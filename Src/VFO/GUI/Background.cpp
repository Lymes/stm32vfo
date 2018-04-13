/*
 * Background.cpp
 *
 *  Created on: Apr 8, 2018
 *      Author: lymes
 */

#include "Background.h"

#include "ST7735/st7735.h"

namespace VFO
{

BitmapBox::BitmapBox(uint8_t x, uint8_t y, Bitmap *bitmap)
{
	_x = x;
	_y = y;
	_data = bitmap;
}

uint16_t BitmapBox::getBackColor(uint8_t x, uint8_t y)
{
	return *(_data->data + y * 160 + x);
}

void BitmapBox::draw()
{
	CS_L();
	ST7735_AddrSet(_x, _y, _x + _data->width, _y + _data->height);
	A0_H();
	uint16_t *ptr = (uint16_t *) _data->data;
	for (int i = 0; i < _data->width * _data->height; i++)
	{
		uint16_t color = *ptr++;
		ST7735_write(color >> 8);
		ST7735_write((uint8_t) color);
	}

	CS_H();
}

GradientBox::GradientBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	_x = x, _y = y, _w = w, _h = h;
}

uint16_t GradientBox::getBackColor(uint8_t x, uint8_t y)
{
	uint16_t absY = y - _y;
	uint16_t absX = x - _x;
	RGB rowStart =
	{
			(uint8_t) (upLeft.r + (downLeft.r - upLeft.r) * absY / _h),
			(uint8_t) (upLeft.g + (downLeft.g - upLeft.g) * absY / _h),
			(uint8_t) (upLeft.b + (downLeft.b - upLeft.b) * absY / _h),
	};
	RGB rowEnd =
	{
			(uint8_t) (upRight.r + (downRight.r - upRight.r) * absY / _h),
			(uint8_t) (upRight.g + (downRight.g - upRight.g) * absY / _h),
			(uint8_t) (upRight.b + (downRight.b - upRight.b) * absY / _h),
	};
	RGB pix =
	{
			(uint8_t) (rowStart.r + (rowEnd.r - rowStart.r) * absX / _w),
			(uint8_t) (rowStart.g + (rowEnd.g - rowStart.g) * absX / _w),
			(uint8_t) (rowStart.b + (rowEnd.b - rowStart.b) * absX / _w),
	};

	return ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);

}

void GradientBox::draw()
{
	CS_L();
	ST7735_AddrSet(_x, _y, _x + _w - 1, _y + _h - 1);
	A0_H();

	uint16_t color;
	uint8_t row, col;
	RGB rowStart, rowEnd, pix;
	for (row = 0; row < _h; row++)
	{
		rowStart =
		{
			(uint8_t)(upLeft.r + (downLeft.r - upLeft.r) * row / _h),
			(uint8_t)(upLeft.g + (downLeft.g - upLeft.g) * row / _h),
			(uint8_t)(upLeft.b + (downLeft.b - upLeft.b) * row / _h),
		};
		rowEnd =
		{
			(uint8_t)(upRight.r + (downRight.r - upRight.r) * row / _h),
			(uint8_t)(upRight.g + (downRight.g - upRight.g) * row / _h),
			(uint8_t)(upRight.b + (downRight.b - upRight.b) * row / _h),
		};

		for (col = 0; col < _w; col++)
		{
			pix =
			{
				(uint8_t)(rowStart.r + (rowEnd.r - rowStart.r) * col / _w),
				(uint8_t)(rowStart.g + (rowEnd.g - rowStart.g) * col / _w),
				(uint8_t)(rowStart.b + (rowEnd.b - rowStart.b) * col / _w),
			};

			color = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
			ST7735_write(color >> 8);
			ST7735_write((uint8_t)color);
		}
	}

	CS_H();
}


void GradientBox::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	_x = x; _y = y; _w = w; _h = h;
	draw();
}


void GradientBox::clear(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	CS_L();
	ST7735_AddrSet(x, y, x + w - 1, y + h - 1);
	A0_H();

	uint16_t color;
	uint8_t row, col;
	RGB rowStart, rowEnd, pix;
	for (row = y; row < y + h; row++)
	{
		rowStart =
		{
			(uint8_t)(upLeft.r + (downLeft.r - upLeft.r) * row / _h),
			(uint8_t)(upLeft.g + (downLeft.g - upLeft.g) * row / _h),
			(uint8_t)(upLeft.b + (downLeft.b - upLeft.b) * row / _h),
		};
		rowEnd =
		{
			(uint8_t)(upRight.r + (downRight.r - upRight.r) * row / _h),
			(uint8_t)(upRight.g + (downRight.g - upRight.g) * row / _h),
			(uint8_t)(upRight.b + (downRight.b - upRight.b) * row / _h),
		};

		for (col = x; col < x + w; col++)
		{
			pix =
			{
				(uint8_t)(rowStart.r + (rowEnd.r - rowStart.r) * col / _w),
				(uint8_t)(rowStart.g + (rowEnd.g - rowStart.g) * col / _w),
				(uint8_t)(rowStart.b + (rowEnd.b - rowStart.b) * col / _w),
			};

			color = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
			ST7735_write(color >> 8);
			ST7735_write((uint8_t)color);
		}
	}

	CS_H();
}


uint16_t backgroundColor(void *ptr, uint16_t x, uint16_t y)
{
	return ((Background *) ptr)->getBackColor(x, y);
}

} /* namespace VFO */
