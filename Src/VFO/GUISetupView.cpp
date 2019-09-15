/*
 * GUISetupView.cpp
 *
 *  Created on: Apr 6, 2018
 *      Author: lymes
 */

#include "GUISetupView.h"
#include "ConfigHelpers.h"
#include "GUI/Utils.h"

#include "stm32f103xb.h"
#include "stm32f1xx_ll_adc.h"

#define TOP_OFFS 34
#define ITEM_HEIGHT 14

extern uint16_t readVoltage(ADC_TypeDef *ADCx, uint8_t channel);

namespace VFO
{

const struct SetupItem menu =
	{
		"Установки",
		NULL,
		NULL,
		NULL,
		false,
		5,
		(struct SetupItem[]){
			{"Калибровка",
			 _getCalibration,
			 _setCalibration,
			 NULL,
			 false,
			 0,
			 NULL},
			{"Ниж. скат",
			 _getQFilter1,
			 _setQFilter1,
			 NULL,
			 false,
			 0,
			 NULL},
			{"Верх. скат",
			 _getQFilter2,
			 _setQFilter2,
			 NULL,
			 false,
			 0,
			 NULL},
			{"Шифт опор.",
			 _getBFOffset,
			 _setBFOffset,
			 NULL,
			 true,
			 0,
			 NULL},
			{"Разное",
			 NULL,
			 NULL,
			 NULL,
			 false,
			 4,
			 (struct SetupItem[]){
				 {"Яркость экрана",
				  _getBrightness,
				  _setBrightness,
				  NULL,
				  true,
				  0,
				  NULL},
				 {"Энкодер",
				  _getEncoder,
				  _setEncoder,
				  NULL,
				  true,
				  0,
				  NULL},
				 {"Делитель Uin",
				  _getCalibrationUin,
				  _setCalibrationUin,
				  NULL,
				  true,
				  0,
				  NULL},
				 {"Сброс настроек",
				  NULL,
				  NULL,
				  _resetConfig,
				  false,
				  0,
				  NULL}}}}};

GUISetupView::GUISetupView()
{
	_parent = NULL;
	_currentItem = &menu;
	_selectedChild = NULL;
	init();
}

GUISetupView::GUISetupView(SetupItem *item, GUISetupView *parent)
{
	_parent = parent;
	_currentItem = item;
	_selectedChild = NULL;
	init();
}

void GUISetupView::init()
{
	_window = new GradientBox(0, 0, 160, 128);
	_window->downLeft = {200, 10, 20};
	_window->downRight = {150, 0, 200};
	_window->upLeft = {60, 0, 40};
	_window->upRight = {200, 160, 20};

	_header = new GradientBox(2, 2, 156, 25);
	_header->downLeft = {10, 10, 10};
	_header->downRight = {10, 10, 10};
	_header->upLeft = {100, 100, 100};
	_header->upRight = {100, 100, 100};

	_selection = new GradientBox(2, 2, 156, 15);
	_selection->upLeft = {10, 160, 10};
	_selection->upRight = {10, 160, 10};
	_selection->downLeft = {10, 10, 100};
	_selection->downRight = {10, 10, 100};

	_btnBack = new GradientBox(6, 105, 60, 20);
	_btnBack->downLeft = {10, 10, 10};
	_btnBack->downRight = {10, 10, 10};
	_btnBack->upLeft = {100, 100, 100};
	_btnBack->upRight = {100, 100, 100};
}

GUISetupView::~GUISetupView()
{
	delete _header;
	delete _window;
	delete _btnBack;
}

// Callbacks

void GUISetupView::pushEncoderIncrement(int16_t increment, uint16_t period)
{
	if (_selectedChild)
	{
		_selectedChild->pushEncoderIncrement(increment, period);
		return;
	}

	if (!_editing)
	{
		_encCounter += increment;
		if (abs(_encCounter) < _getEncoder() * 3) /* full rotation step */
		{
			return;
		}
		_encCounter = 0;

		uint8_t selection;
		if (increment < 0)
		{
			selection = _selectedItem == 0 ? _currentItem->numChildren : _selectedItem - 1;
		}
		else
		{
			selection = _selectedItem == _currentItem->numChildren ? 0 : _selectedItem + 1;
		}
		setSelected(selection);
	}
	else
	{
		if (_currentItem->children[_selectedItem].slow)
		{
			_encCounter += increment;
			if (abs(_encCounter) < _getEncoder() * 3) /* half rotation step */
			{
				return;
			}
			_encCounter = 0;
			increment = increment > 0 ? 1 : -1;
		}

		uint32_t value = _currentItem->children[_selectedItem].getter();
		value += increment;
		_currentItem->children[_selectedItem].setter(value);
		updateValues();
	}
}

void GUISetupView::menuKeyPressed()
{
	if (_selectedChild)
	{
		_selectedChild->menuKeyPressed();
		return;
	}

	if (_selectedItem >= _currentItem->numChildren)
	{
		if (_parent)
		{
			VFOC->scrollAnimation();
			_parent->draw();
			_parent->setSelectedChild(NULL);
		}
		else
		{
			VFOC->triggerMemoryWrite();
			VFOC->showMain();
			return;
		}
	}
	else
	{
		if (_currentItem->children[_selectedItem].getter == NULL && _currentItem->children[_selectedItem].cmd == NULL) // submenu
		{
			GUISetupView *submenu = new GUISetupView(&_currentItem->children[_selectedItem], this);
			setSelectedChild(submenu);
			VFOC->scrollAnimation();
			submenu->draw();
		}
		else if (_currentItem->children[_selectedItem].cmd) // command
		{
			_currentItem->children[_selectedItem].cmd();
			updateValues();
		}
		else
		{
			_editing = !_editing;
			updateValues();
		}
	}
}

// Utilities

void GUISetupView::setSelected(uint8_t selected)
{
	// clear old selection
	if (_selectedItem == _currentItem->numChildren)
	{
		drawBackButton(false);
	}
	else
	{
		drawItemTitle(_selectedItem, false);
	}

	_selectedItem = selected;

	// draw new selection
	if (_selectedItem == _currentItem->numChildren)
	{
		drawBackButton(true);
	}
	else
	{
		drawItemTitle(_selectedItem, true);
	}

	this->updateValues();
}

void GUISetupView::updateValues()
{
	uint8_t i = 0;
	for (; i < _currentItem->numChildren; i++)
	{
		drawValue(i, _selectedItem == i, _editing);
	}
}

void GUISetupView::setSelectedChild(GUISetupView *child)
{
	if (!child && _selectedChild)
	{
		delete _selectedChild;
	}
	_selectedChild = child;
}

// Drawing methods

void GUISetupView::draw()
{
	this->drawBackground();
	this->setSelected(_currentItem->numChildren);
	drawBackButton(true);
}

void GUISetupView::drawBackground()
{
	_window->draw();
	_header->draw();
	drawWindowTitle();

	uint8_t i = 0;
	for (; i < _currentItem->numChildren; i++)
	{
		drawItemTitle(i, false);
	}
}

void GUISetupView::drawWindowTitle()
{
	char str1[20];
	VFO::utf8to1251Dest(_currentItem->name, str1, sizeof(str1));
	uint8_t xpos = (160 - strlen(str1) * 8) / 2;
	ST7735_PutStr7x11Ex(xpos, 8, str1, COLOR565_YELLOW, _header, VFO::backgroundColor);
}

void GUISetupView::drawItemTitle(uint8_t itemIndex, bool selected)
{
	char str1[20];
	if (selected)
	{
		_selection->draw(2, TOP_OFFS - 4 + itemIndex * ITEM_HEIGHT, 156, ITEM_HEIGHT);
	}
	else
	{
		_window->clear(2, TOP_OFFS - 4 + itemIndex * ITEM_HEIGHT, 156, ITEM_HEIGHT);
	}
	const SetupItem *item = &(_currentItem->children[itemIndex]);
	ST7735_PutStr5x7Ex(1, 6, TOP_OFFS + itemIndex * ITEM_HEIGHT, VFO::utf8to1251Dest(item->name, str1, sizeof(str1)),
					   selected ? COLOR565_WHITE : COLOR565_YELLOW, selected ? _selection : _window, VFO::backgroundColor);
}

void GUISetupView::drawValue(uint8_t itemIndex, bool selected, bool edited)
{
	char str[10];
	uint16_t color = COLOR565_YELLOW;
	if (selected)
	{
		color = edited ? COLOR565_RED : COLOR565_WHITE;
	}
	const SetupItem *item = &(_currentItem->children[itemIndex]);
	if (item->getter)
	{
		uint32_t value = item->getter();
		ST7735_PutStr5x7Ex(1, 100, TOP_OFFS + itemIndex * ITEM_HEIGHT, (char *)valToStr(value, str, sizeof(str), 0),
						   color,
						   selected ? _selection : _window,
						   VFO::backgroundColor);
	}
	else if (item->cmd) // command
	{
	}
	else // submenu
	{
		ST7735_PutStr5x7Ex(1, 148, TOP_OFFS + itemIndex * ITEM_HEIGHT, (char *)">",
						   selected ? COLOR565_WHITE : COLOR565_YELLOW,
						   selected ? _selection : _window,
						   VFO::backgroundColor);
	}
}

void GUISetupView::drawBackButton(bool selected)
{
	char str1[6];
	uint16_t color = COLOR565_YELLOW;
	if (selected)
	{
		_btnBack->upLeft = {10, 160, 10};
		_btnBack->upRight = {10, 160, 10};
		_btnBack->downLeft = {10, 10, 100};
		_btnBack->downRight = {10, 10, 100};
		color = COLOR565_WHITE;
	}
	else
	{
		_btnBack->downLeft = {10, 10, 10};
		_btnBack->downRight = {10, 10, 10};
		_btnBack->upLeft = {100, 100, 100};
		_btnBack->upRight = {100, 100, 100};
	}
	_btnBack->draw();
	ST7735_PutStr5x7Ex(1, 21, 111, VFO::utf8to1251Dest("Назад", str1, sizeof(str1)),
					   color, _btnBack, VFO::backgroundColor);
}

void GUISetupView::showVoltage(uint32_t value)
{
	char buf[6];
	ST7735_PutStr5x7Ex(1, 120, 110, VFO::voltageToStr(value, buf, 6),
					   COLOR565_WHITE, _window, VFO::backgroundColor);
}

} /* namespace VFO */
