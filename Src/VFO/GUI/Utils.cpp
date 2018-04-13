/*
 * Utils.cpp
 *
 *  Created on: Apr 8, 2018
 *      Author: lymes
 */

#include "Utils.h"

namespace VFO
{

char *valToStr(int32_t val, char *buf, size_t bufSize, char sepChar)
{
	// validate the parameters, return null on error
	if ((bufSize < 2) || (buf == 0))
	{
		return 0;
	}

	// put a null at the end of the buffer, adjust the size
	buf += bufSize--;
	*(--buf) = '\0';

	// special case: value equal zero
	if (val == 0)
	{
		*(--buf) = '0';
		bufSize--;
	}

	// special case: value is negative
	bool negative = false;
	if (val < 0)
	{
		val = -val;
		negative = true;
	}

	uint8_t digCnt = 0;

	// general case: possibly multiple digits with thousands separators
	while (bufSize)
	{
		// add a thousands separator every three digits
		if (sepChar && (digCnt >= 3) && (bufSize > 1))
		{
			*(--buf) = sepChar;
			bufSize--;
			digCnt = 0;
		}
		if (val == 0)
		{
			if (*buf == '.') // first symbol cannot be separator
			{
				buf++;
				bufSize++;
			}
			if (negative) // put minus symbol
			{
				*(--buf) = '-';
				negative = false;
			}
			else
			{
				*(--buf) = ' '; // nothing to do, put space
			}
		}
		else
		{
			// add another digit to the buffer
			*(--buf) = (char) (val % 10) | '0';
			digCnt++;
			// prepare for producing the next digit
			val /= 10;
		}
		bufSize--;
	}

	// return a pointer to the completed string
	return (buf);
}


char* utf8to1251Dest(const char *utf8, char *dest, size_t len)
{
	int i = 0;
	size_t j = 0;
	for (; utf8[i] != 0 && j < len; ++i)
	{
		char prefix = utf8[i];
		char suffix = utf8[i + 1];
		if ((prefix & 0x80) == 0)
		{
			dest[j] = (char) prefix;
			++j;
		}
		else if ((~prefix) & 0x20)
		{
			int first5bit = prefix & 0x1F;
			first5bit <<= 6;
			int sec6bit = suffix & 0x3F;
			int unicode_char = first5bit + sec6bit;

			if (unicode_char >= 0x410 && unicode_char <= 0x44F)
			{
				dest[j] = (char) (unicode_char - 0x350);
			}
			else if (unicode_char >= 0x80 && unicode_char <= 0xFF)
			{
				dest[j] = (char) (unicode_char);
			}
			else if (unicode_char >= 0x402 && unicode_char <= 0x403)
			{
				dest[j] = (char) (unicode_char - 0x382);
			}
			else
			{
				// can't convert this char
				return 0;
			}
			++i;
			++j;
		}
		else
		{
			// can't convert this chars
			return 0;
		}
	}
	dest[j] = 0;
	return dest;
}


char* utf8to1251(char *utf8)
{
	int i = 0;
	int j = 0;
	for (; utf8[i] != 0; ++i)
	{
		char prefix = utf8[i];
		char suffix = utf8[i + 1];
		if ((prefix & 0x80) == 0)
		{
			utf8[j] = (char) prefix;
			++j;
		}
		else if ((~prefix) & 0x20)
		{
			int first5bit = prefix & 0x1F;
			first5bit <<= 6;
			int sec6bit = suffix & 0x3F;
			int unicode_char = first5bit + sec6bit;

			if (unicode_char >= 0x410 && unicode_char <= 0x44F)
			{
				utf8[j] = (char) (unicode_char - 0x350);
			}
			else if (unicode_char >= 0x80 && unicode_char <= 0xFF)
			{
				utf8[j] = (char) (unicode_char);
			}
			else if (unicode_char >= 0x402 && unicode_char <= 0x403)
			{
				utf8[j] = (char) (unicode_char - 0x382);
			}
			else
			{
				// can't convert this char
				return 0;
			}
			++i;
			++j;
		}
		else
		{
			// can't convert this chars
			return 0;
		}
	}
	utf8[j] = 0;
	return utf8;
}

} /* namespace VFO */
