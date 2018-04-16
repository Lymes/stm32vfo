/*
 * GUIMainView.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#include "GUIMainView.h"
#include "VFOController.h"

#include "GUI/Utils.h"

extern VFO::VFOController *_mainController;


namespace VFO
{

GUIMainView::GUIMainView()
{
	_window = new GradientBox(0, 0, 160, 128);

	_btn1 = new GradientBox(10, 50, 40, 25);
	_btn1->downLeft = {10, 10, 10};
	_btn1->downRight = {10, 10, 10};
	_btn1->upLeft = {100, 100, 100};
	_btn1->upRight = {100, 100, 100};

	_btn2 = new GradientBox(60, 50, 40, 25);
	_btn2->downLeft = {10, 10, 10};
	_btn2->downRight = {10, 10, 10};
	_btn2->upLeft = {100, 100, 100};
	_btn2->upRight = {100, 100, 100};

	_btn3 = new GradientBox(110, 50, 40, 25);
	_btn3->downLeft = {10, 10, 10};
	_btn3->downRight = {10, 10, 10};
	_btn3->upLeft = {100, 100, 100};
	_btn3->upRight = {100, 100, 100};

	_freqString = new FrequencyString(0, 10, _window);
	_sMeter = new SMeter(10, 90, _window);
}

GUIMainView::~GUIMainView()
{
	delete _btn1;
	delete _btn2;
	delete _btn3;
	delete _window;
}

void GUIMainView::menuKeyPressed()
{
	_mainController->showSetup();
}


void GUIMainView::draw()
{
	this->drawBackground();

	_freqString->setBackground(_window);
	_freqString->draw(_mainController->getConfig()->getFrequency());
}

void GUIMainView::drawBackground()
{
	_window->draw();

	_btn1->draw();
	_btn2->draw();
	_btn3->draw();

	ST7735_Rect(10,  50, 50,  75, COLOR565_WHITE);
	ST7735_Rect(60,  50, 100, 75, COLOR565_WHITE);
	ST7735_Rect(110, 50, 150, 75, COLOR565_WHITE);

	char tt[] = "SSB";
	ST7735_PutStr7x11Ex(18, 57, VFO::utf8to1251(tt), COLOR565_YELLOW, _btn1,
			VFO::backgroundColor);

	_sMeter->draw(255);

}


void GUIMainView::pushEncoderIncrement(int16_t increment, uint16_t period)
{
	uint32_t freq = _mainController->getConfig()->getFrequency();

	uint16_t factor = abs(increment / period) > 10 ? 10000 : 10;
	freq += increment * factor / period;
	_mainController->setFrequency(freq);
	_freqString->draw(freq);
}



} /* namespace VFO */
