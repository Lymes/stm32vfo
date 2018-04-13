/*
 * FrequencyString.h
 *
 *  Created on: Apr 8, 2018
 *      Author: lymes
 */

#ifndef FREQUENCYSTRING_H_
#define FREQUENCYSTRING_H_

#include "Background.h"

namespace VFO
{

class FrequencyString
{
	uint8_t _longBuf[12];
	uint16_t _x, _y;
	Background *_back;

public:
	FrequencyString(uint16_t x, uint16_t y, Background *b);

	void setBackground(Background *back);

	void draw(unsigned long freq);

};

} /* namespace VFO */

#endif /* FREQUENCYSTRING_H_ */
