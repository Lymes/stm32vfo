/*
 * GUIView.h
 *
 *  Created on: Apr 6, 2018
 *      Author: lymes
 */

#ifndef VFO_GUIVIEW_H_
#define VFO_GUIVIEW_H_

#include "st7735/st7735.h"

namespace VFO
{

class GUIView
{
protected:
public:
	GUIView();
	virtual ~GUIView();

	virtual void showVoltage(uint32_t value) = 0;

	virtual void draw() = 0;
	virtual void pushEncoderIncrement(int16_t increment, uint16_t period) = 0;
	virtual void menuKeyPressed() = 0;
};

} /* namespace VFO */

#endif /* VFO_GUIVIEW_H_ */
