/*
 * FrequencyString.cpp
 *
 *  Created on: Apr 8, 2018
 *      Author: lymes
 */

#include "FrequencyString.h"
#include "ST7735/st7735.h"
#include "Utils.h"

namespace VFO
{

FrequencyString::FrequencyString(uint8_t x, uint8_t y, Background *b)
{
	_back = b;
	_x = x;
	_y = y;
	memset(_longBuf, 0, sizeof(_longBuf));
}

void FrequencyString::setBackground(Background *back)
{
	_back = back;
	memset(_longBuf, 0, sizeof(_longBuf));
}

void FrequencyString::draw(uint32_t freq)
{
	char buff[12];

	valToStr(freq, buff, sizeof(buff), '.');
	uint8_t x_offs;
	for (uint8_t i = 0; i < sizeof(buff) - 2; i++)
	{
		if (buff[i] != _longBuf[i])
		{
			x_offs = _x + i * 18 - (i / 4) * 12;
			ST7735_PutChar5x7Ex(3, x_offs, _y, buff[i], COLOR565_YELLOW, _back,
					backgroundColor);
			_longBuf[i] = buff[i];
		}
	}
}

} /* namespace VFO */
