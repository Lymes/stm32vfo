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
	return Config->getCalibration();
}

void _setCalibration(int32_t value)
{
	Config->setCalibration(value);
	_mainController->setCalibration(value);
}

int32_t _getCalibrationUin()
{
	return Config->getCalibrationUin();
}

void _setCalibrationUin(int32_t value)
{
	if (value > 100 || value < 1)
	{
		return;
	}
	Config->setCalibrationUin(value);
}

int32_t _getIFrequency()
{
	return Config->getIFrequency();
}

void _setIFrequency(int32_t value)
{
	Config->setIFrequency(value);
}

int32_t _getBFrequency()
{
	return Config->getBFrequency();
}

void _setBFrequency(int32_t value)
{
	Config->setBFrequency(value);
	_mainController->setBFrequency(value);
}

int32_t _getBrightness()
{
	return Config->getBrightness();
}

void _setBrightness(int32_t value)
{
	if (value > 255 || value < 0)
	{
		return;
	}
	Config->setBrightness(value);
	_mainController->setBrightness(value);
}

int32_t _getEncoder()
{
	return Config->getEncoder();
}

void _setEncoder(int32_t value)
{
	if (value < 0)
	{
		return;
	}
	Config->setEncoder(value);
}

void _resetConfig(void)
{
	_mainController->reset();
	//_mainController->triggerMemoryWrite();
}

} // namespace VFO
