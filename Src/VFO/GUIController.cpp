/*
 * GUIController.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#include "GUIController.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace VFO
{

GUIController::GUIController()
{
	ST7735_Init();
	ST7735_Orientation(scr_CCW);

	_setupView = new GUISetupView();
	_mainView = new GUIMainView();

	_currentView = _setupView;
}

GUIController::~GUIController()
{
	delete _setupView;
	delete _mainView;
}

void GUIController::draw()
{
	_currentView->draw();
}

void GUIController::pushEncoderIncrement(int16_t increment)
{
	_currentView->pushEncoderIncrement(increment);
}

void GUIController::menuKeyPressed()
{
	_currentView->menuKeyPressed();
}

void GUIController::showSetup()
{
	_currentView = _setupView;
	_currentView->draw();
}

void GUIController::showMain()
{
	_currentView = _mainView;
	_currentView->draw();
}

} /* namespace VFO */
