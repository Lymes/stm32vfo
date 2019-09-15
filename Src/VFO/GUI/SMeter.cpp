/*
 * SMeter.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: lymes
 */

#include "SMeter.h"
#include "ST7735/st7735.h"

#define WIDTH 130
#define HEIGHT 6
#define COEFF (8 / 10)

namespace VFO
{

SMeter::SMeter(uint8_t x, uint8_t y, Background *back)
{
	_back = back;
	_x = x;
	_y = y;
}

SMeter::~SMeter()
{
}

void SMeter::draw()
{
	drawBackground();
	drawBar();
}

void SMeter::setValue(uint32_t val)
{
	static uint32_t lastPeak = 0;
	_amp = val > 330 ? 330 : val;
	if (_amp > _peak)
	{
		_peak = _amp;
	}
	if (lastPeak * COEFF > _peak)
	{
		_peak = lastPeak * COEFF;
	}
	lastPeak = _peak;
	drawBar();
}

void SMeter::drawBar()
{
	int x = _x;
	int y = _y + 17;

	int a = (_amp * WIDTH) / 330;
	ST7735_FillRect(x, y, x + a, y + HEIGHT, COLOR565_VIOLET);
	ST7735_FillRectEx(x + a + 1, y, WIDTH, y + HEIGHT, _back, VFO::backgroundColor);
	int p = (_peak * WIDTH) / 330;
	ST7735_FillRect(x + p, y, x + p + 1, y + HEIGHT, COLOR565_RED);
}

void SMeter::drawBackground()
{
	ST7735_PutStr5x7Ex(1, _x, _y, (char *)"1  3  5  7  9", COLOR565_WHITE, _back,
					   VFO::backgroundColor);
	ST7735_PutStr5x7Ex(1, _x + 86, _y, (char *)"+20 +60", COLOR565_RED, _back,
					   VFO::backgroundColor);

	ST7735_HLine(_x, 140, _y + 15, COLOR565_WHITE);
	ST7735_HLine(_x, 140, _y + 25, COLOR565_WHITE);

	uint8_t xTick = _x + 2;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
	xTick += 18;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
	xTick += 18;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
	xTick += 18;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
	xTick += 18;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
	xTick += 22;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
	xTick += 24;
	ST7735_VLine(xTick, _y + 10, _y + 15, COLOR565_WHITE);
}

} /* namespace VFO */
