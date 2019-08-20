/*
 * SMeter.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: lymes
 */

#include "SMeter.h"
#include "ST7735/st7735.h"


namespace VFO
{

SMeter::SMeter(uint8_t x, uint8_t y, Background *back)
{
	_back = back;
	_x = x; _y = y;
}

SMeter::~SMeter()
{
}


void SMeter::draw(uint8_t value)
{
	drawBackground();
}


void SMeter::drawBackground()
{
	ST7735_PutStr5x7Ex(1, _x, _y, (char *)"1  3  5  7  9", COLOR565_WHITE, _back,
			VFO::backgroundColor);
	ST7735_PutStr5x7Ex(1, _x + 86, _y, (char *)"+20 +60", COLOR565_RED, _back,
			VFO::backgroundColor);

	ST7735_HLine(_x,  140, _y + 15, COLOR565_WHITE);
	ST7735_HLine(_x,  140, _y + 25, COLOR565_WHITE);

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
