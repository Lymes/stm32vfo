/*
 * GUIController.h
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#ifndef VFO_GUICONTROLLER_H_
#define VFO_GUICONTROLLER_H_

#include "stm32f1xx_hal.h"
#include "GUIMainView.h"
#include "GUISetupView.h"

namespace VFO
{

class GUIController
{
	GUIView *_currentView;

	GUIMainView *_mainView;
	GUISetupView *_setupView;


public:
	GUIController();
	virtual ~GUIController();

	void showSetup();
	void showMain();

	void draw();
	void pushEncoderIncrement(int16_t increment);

	void menuKeyPressed();
};

} /* namespace VFO */

#endif /* VFO_GUICONTROLLER_H_ */
