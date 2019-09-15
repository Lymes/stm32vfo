/*
 * GUIMainView.h
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#ifndef VFO_GUIMAINVIEW_H_
#define VFO_GUIMAINVIEW_H_

#include "GUIView.h"
#include "GUI/Background.h"
#include "GUI/FrequencyString.h"
#include "GUI/SMeter.h"

namespace VFO
{

class GUIMainView : public GUIView
{
	GradientBox *_window;
	GradientBox *_btn1;
	GradientBox *_btn2;
	GradientBox *_btn3;
	FrequencyString *_freqString;
	SMeter *_sMeter;

public:
	GUIMainView();
	virtual ~GUIMainView();

	void drawOpMode();

	virtual void draw();
	virtual void pushEncoderIncrement(int16_t increment, uint16_t period);
	virtual void menuKeyPressed();

	virtual void showVoltage(uint32_t value);
	virtual void showSMeter(uint32_t value);

private:
	void drawBackground();
	void drawFrequency(unsigned long frequency);

	void drawFrequency(uint8_t x, uint8_t y, unsigned long frequency);
};

} /* namespace VFO */

#endif /* VFO_GUIMAINVIEW_H_ */
