/*
 * GUIMainView.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#include "GUIMainView.h"
#include "VFOController.h"
#include "GUI/Utils.h"

#define ENCODER_THRESHOLD 4

namespace VFO
{

GUIMainView::GUIMainView()
{
	_window = new GradientBox(0, 0, 160, 128);

	_btn1 = new GradientBox(10, 50, 40, 25);
	_btn1->downLeft =
		{10, 10, 10};
	_btn1->downRight =
		{10, 10, 10};
	_btn1->upLeft =
		{100, 100, 100};
	_btn1->upRight =
		{100, 100, 100};

	_btn2 = new GradientBox(60, 50, 40, 25);
	_btn2->downLeft =
		{10, 10, 10};
	_btn2->downRight =
		{10, 10, 10};
	_btn2->upLeft =
		{100, 100, 100};
	_btn2->upRight =
		{100, 100, 100};

	_btn3 = new GradientBox(110, 50, 40, 25);
	_btn3->downLeft =
		{10, 10, 10};
	_btn3->downRight =
		{10, 10, 10};
	_btn3->upLeft =
		{100, 100, 100};
	_btn3->upRight =
		{100, 100, 100};

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
	VFOC->showSetup();
}

void GUIMainView::draw()
{
	this->drawBackground();

	_freqString->setBackground(_window);
	_freqString->draw(Config->getFrequency());
}

void GUIMainView::drawOpMode()
{
	char tt[4];
	strcpy(tt, ((VFOC->opMode() == OP_LSB) ? "LSB" : "USB"));
	ST7735_PutStr7x11Ex(18, 57, VFO::utf8to1251(tt), COLOR565_YELLOW, _btn1,
						VFO::backgroundColor);
}

void GUIMainView::drawBackground()
{
	_window->draw();

	_btn1->draw();
	_btn2->draw();
	_btn3->draw();

	ST7735_Rect(10, 50, 50, 75, COLOR565_WHITE);
	ST7735_Rect(60, 50, 100, 75, COLOR565_WHITE);
	ST7735_Rect(110, 50, 150, 75, COLOR565_WHITE);

	drawOpMode();

	_sMeter->draw();
}

void GUIMainView::pushEncoderIncrement(int16_t increment, uint16_t period)
{
	uint32_t freq = Config->getFrequency();
	uint16_t encoderRes = Config->getEncoder();

	uint16_t factor = 1;
	// if (abs(increment) > (encoderRes / 2)) // half rotation
	// {
	// 	factor = 100;
	// }
	if (abs(increment) > (encoderRes / 4)) // quarter rotation
	{
		factor = 10;
	}
	freq += increment * factor / ENCODER_THRESHOLD;
	VFOC->setFrequency(freq);
	VFOC->triggerMemoryWrite();

	_freqString->draw(freq);
}

void GUIMainView::showVoltage(uint32_t value)
{
	char buf[6];
	ST7735_PutStr5x7Ex(1, 116, 60, VFO::voltageToStr(value, buf, 6),
					   COLOR565_WHITE, _btn3, VFO::backgroundColor);
}

void GUIMainView::showSMeter(uint32_t value)
{
	_sMeter->setValue(value);
}

} /* namespace VFO */
