/*
 * SMeter.h
 *
 *  Created on: Apr 15, 2018
 *      Author: lymes
 */

#ifndef VFO_GUI_SMETER_H_
#define VFO_GUI_SMETER_H_

#include "Background.h"


namespace VFO
{

class SMeter
{
	uint8_t _x, _y;
	Background *_back;

public:
	SMeter(uint8_t x, uint8_t y, Background *back);
	virtual ~SMeter();

	void draw( uint8_t value );

private:
	void drawBackground();
};

} /* namespace VFO */

#endif /* VFO_GUI_SMETER_H_ */
