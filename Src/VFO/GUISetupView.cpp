/*
 * GUISetupView.cpp
 *
 *  Created on: Apr 6, 2018
 *      Author: lymes
 */

#include "GUISetupView.h"
#include "ConfigHelpers.h"

#include "GUI/Utils.h"

namespace VFO
{

const struct SetupItem menu =
{
	"Установки",
	NULL,
	NULL,
	NULL,
	4,
	(struct SetupItem[])
	{
		{
			"Калибровка",
			_getCalibration,
			_setCalibration,
			NULL,
			0,
			NULL
		},
		{
			"Установка ПЧ",
			_getIFrequency,
			_setIFrequency,
			NULL,
			0,
			NULL
		},
		{
			"Установка OпЧ",
			_getBFrequency,
			_setBFrequency,
			NULL,
			0,
			NULL
		},
		{
			"Разное",
			NULL,
			NULL,
			NULL,
			3,
			(struct SetupItem[])
			{
				{
					"Яркость экр",
					_getBrightness,
					_setBrightness,
					NULL,
					0,
					NULL
				},
				{
					"Энкодер",
					_getEncoder,
					_setEncoder,
					NULL,
					0,
					NULL
				},
				{
					"Сброс настроек",
					NULL,
					NULL,
					_resetConfig,
					0,
					NULL
				}
			}
		}
	}
};



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
	_window->downLeft  = { 200, 10, 20 };
	_window->downRight = { 150, 0, 200 };
	_window->upLeft    = { 60, 0, 40 };
	_window->upRight   = { 200, 160, 20 };

	_header = new GradientBox(2, 2, 156, 25);
	_header->downLeft  = { 10, 10, 10 };
	_header->downRight = { 10, 10, 10 };
	_header->upLeft    = { 100, 100, 100 };
	_header->upRight   = { 100, 100, 100};

	_selection = new GradientBox(2, 2, 156, 15);
	_selection->upLeft  = { 10, 160, 10 };
	_selection->upRight = { 10, 160, 10 };
	_selection->downLeft  = { 10, 10, 100 };
	_selection->downRight = { 10, 10, 100 };

	_btnBack = new GradientBox(6, 105, 60, 20);
	_btnBack->downLeft  = { 10, 10, 10 };
	_btnBack->downRight = { 10, 10, 10 };
	_btnBack->upLeft    = { 100, 100, 100 };
	_btnBack->upRight   = { 100, 100, 100};
}

GUISetupView::~GUISetupView()
{
	delete _header;
	delete _window;
}

void GUISetupView::pushEncoderIncrement(int16_t increment)
{
	if ( _selectedChild )
	{
		_selectedChild->pushEncoderIncrement(increment);
		return;
	}

	if (!_editing)
	{
		_encCounter += increment;
		if (abs(_encCounter) < _getEncoder()) /*  */
		{
			return;
		}
		_encCounter = 0;

		uint8_t selection;
		if (increment < 0)
		{
			selection =
					_selectedItem == 0 ? _currentItem->numChildren : _selectedItem - 1;
		}
		else
		{
			selection =
					_selectedItem == _currentItem->numChildren ? 0 : _selectedItem + 1;
		}
		setSelected(selection);
	}
	else
	{
		uint32_t value = _currentItem->children[ _selectedItem ].getter();
		value += increment;
		_currentItem->children[ _selectedItem ].setter(value);
		updateValues();
	}
}

void GUISetupView::setSelected(uint8_t selected)
{
	// clear old selection
	if ( _selectedItem == _currentItem->numChildren )
	{
		drawBackButton(false);
	}
	else
	{
		_window->clear(2, 36 + _selectedItem * 15, 156, 15);
	}

	_selectedItem = selected;

	char str1[15];
	uint8_t i = 0;
	for (; i < _currentItem->numChildren; i++)
	{
		if (_selectedItem == i )
		{
			_selection->draw(2, 36 + i * 15, 156, 15);
		}
		const SetupItem *item = &(_currentItem->children[i]);
		ST7735_PutStr5x7Ex(1, 6, 40 + i * 15, VFO::utf8to1251Dest(item->name, str1, sizeof(str1)),
				_selectedItem == i ? COLOR565_WHITE : COLOR565_YELLOW,
				_selectedItem == i ? _selection : _window,
				VFO::backgroundColor);
	}

	if ( _selectedItem == _currentItem->numChildren )
	{
		drawBackButton(true);
	}

	this->updateValues();
}

void GUISetupView::drawBackButton(bool selected)
{
	char str1[6];
	uint16_t color = COLOR565_YELLOW;
	if ( selected )
	{
		_btnBack->upLeft  = { 10, 160, 10 };
		_btnBack->upRight = { 10, 160, 10 };
		_btnBack->downLeft    = { 10, 10, 100 };
		_btnBack->downRight   = { 10, 10, 100 };
		color = COLOR565_WHITE;
	}
	else
	{
		_btnBack->downLeft  = { 10, 10, 10 };
		_btnBack->downRight = { 10, 10, 10 };
		_btnBack->upLeft    = { 100, 100, 100 };
		_btnBack->upRight   = { 100, 100, 100};
	}
	_btnBack->draw();
	ST7735_PutStr5x7Ex(1, 21, 111, VFO::utf8to1251Dest("Назад", str1, sizeof(str1)),
			color, _btnBack, VFO::backgroundColor);
}

void GUISetupView::updateValues()
{
	char str[10];
	uint8_t i = 0;
	for (; i < _currentItem->numChildren; i++)
	{
		uint16_t color = COLOR565_YELLOW;
		if ( _selectedItem == i )
		{
			color = _editing ? COLOR565_RED : COLOR565_WHITE;
		}
		const SetupItem *item = &(_currentItem->children[i]);
		if ( item->getter )
		{
			uint32_t value = item->getter();
			ST7735_PutStr5x7Ex(1, 100, 40 + i * 15, (char *) valToStr(value, str, sizeof(str), 0),
				color,
				_selectedItem == i ? _selection : _window,
				VFO::backgroundColor);
		}
		else if (item->cmd ) // command
		{

		}
		else // submenu
		{
			ST7735_PutStr5x7Ex(1, 148, 40 + i * 15, (char *)">",
				_selectedItem == i ? COLOR565_WHITE : COLOR565_YELLOW,
				_selectedItem == i ? _selection : _window,
				VFO::backgroundColor);
		}
	}
}

void GUISetupView::setSelectedChild( GUISetupView *child )
{
	if ( !child && _selectedChild )
	{
		delete _selectedChild;
	}
	_selectedChild = child;
}

void GUISetupView::menuKeyPressed()
{
	if ( _selectedChild )
	{
		_selectedChild->menuKeyPressed();
		return;
	}

	if ( _selectedItem >= _currentItem->numChildren )
	{
		if ( _parent )
		{
			_parent->draw();
			_parent->setSelectedChild(NULL);
		}
		else
		{
			_mainController->storeConfiguration();
			_mainController->showMain();
			return;
		}
	}
	else
	{
		if ( _currentItem->children[ _selectedItem ].getter == NULL && _currentItem->children[ _selectedItem ].cmd == NULL) // submenu
		{
			GUISetupView *submenu = new GUISetupView( &_currentItem->children[ _selectedItem ], this );
			setSelectedChild( submenu );
			submenu->draw();
		}
		else if ( _currentItem->children[ _selectedItem ].cmd ) // command
		{
			_currentItem->children[ _selectedItem ].cmd();
			updateValues();
		}
		else
		{
			_editing = !_editing;
			updateValues();
		}
	}
}

void GUISetupView::draw()
{
	this->drawBackground();
	this->setSelected(0);
	drawBackButton(false);
}

void GUISetupView::drawBackground()
{
	_window->draw();
	_header->draw();
	char str1[20];
	VFO::utf8to1251Dest(_currentItem->name, str1, sizeof(str1));
	uint8_t xpos = (160 - strlen(str1) * 8) / 2;
	ST7735_PutStr7x11Ex(xpos, 8, str1, COLOR565_YELLOW, _header, VFO::backgroundColor);
}

} /* namespace VFO */
