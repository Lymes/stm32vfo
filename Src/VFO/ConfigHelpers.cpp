/*
 * ConfigHelpers.cpp
 *
 *  Created on: Apr 13, 2018
 *      Author: lymes
 */

#include "ConfigHelpers.h"

namespace VFO
{

int32_t _getCalibration()
{
	return _mainController->getConfig()->getCalibration();
}

void _setCalibration(int32_t value)
{
	_mainController->getConfig()->setCalibration(value);
	_mainController->setCalibration(value);
}

int32_t _getIFrequency()
{
	return _mainController->getConfig()->getIFrequency();
}

void _setIFrequency(int32_t value)
{
	_mainController->getConfig()->setIFrequency(value);
}

int32_t _getBFrequency()
{
	return _mainController->getConfig()->getBFrequency();
}

void _setBFrequency(int32_t value)
{
	_mainController->getConfig()->setBFrequency(value);
}

int32_t _getBrightness()
{
	return _mainController->getConfig()->getBrightness();
}

void _setBrightness(int32_t value)
{
	if ( value > 255 || value < 0 )
	{
		return;
	}
	_mainController->getConfig()->setBrightness(value);
	_mainController->setBrightness(value);
}

int32_t _getEncoder()
{
	return _mainController->getConfig()->getEncoder();
}
void _setEncoder(int32_t value)
{
	_mainController->getConfig()->setEncoder(value);
}

void _resetConfig(void)
{
	_mainController->reset();
}

}
