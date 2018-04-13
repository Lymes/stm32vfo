/*
 * Background.h
 *
 *  Created on: Apr 8, 2018
 *      Author: lymes
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "stm32f1xx_hal.h"
#include <stdlib.h>

#include "Bitmap.h"

namespace VFO
{

struct RGB
{
	uint8_t r, g, b;
};

class Background
{

	uint16_t _backColor;

public:
	Background()
	{
		_backColor = 0;
	}
	Background(uint16_t c)
	{
		_backColor = c;
	}

	virtual ~Background()
	{
	}

	virtual uint16_t getBackColor(uint8_t x, uint8_t y)
	{
		return _backColor;
	}

};

class BitmapBox: public Background
{
	Bitmap *_data;
	uint8_t _x, _y;

public:
	BitmapBox(uint8_t x, uint8_t y, Bitmap *bitmap);
	virtual ~BitmapBox()
	{
	}

	virtual uint16_t getBackColor(uint8_t x, uint8_t y);

	void draw();
};

class GradientBox: public Background
{

public:
	RGB upLeft    = { 0, 40, 80 };
	RGB upRight   = { 140, 10, 10 };
	RGB downLeft  = { 140, 128, 0 };
	RGB downRight = { 0, 128, 140 };

	GradientBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	virtual ~GradientBox()
	{
	}

	virtual uint16_t getBackColor(uint8_t x, uint8_t y);

	void draw();
	void draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	void clear(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

private:
	uint8_t _x, _y, _w, _h;

};

uint16_t backgroundColor(void *ptr, uint16_t x, uint16_t y);

} /* namespace VFO */

#endif /* BACKGROUND_H_ */
