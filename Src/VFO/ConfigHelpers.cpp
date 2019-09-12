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
	VFOC->setCalibration(value);
}

int32_t _getCalibrationUin()
{
	return Config->getCalibrationUin();
}

void _setCalibrationUin(int32_t value)
{
	if (value > 200 || value < 1)
	{
		return;
	}
	Config->setCalibrationUin(value);
}

int32_t _getQFilter1()
{
	return Config->getQFilter1();
}

void _setQFilter1(int32_t value)
{
	Config->setQFilter1(value);
	VFOC->setFrequency(Config->getFrequency());
}

int32_t _getQFilter2()
{
	return Config->getQFilter2();
}

void _setQFilter2(int32_t value)
{
	Config->setQFilter2(value);
	VFOC->setFrequency(Config->getFrequency());
}

int32_t _getBFOffset()
{
	return Config->getBFOffset();
}

void _setBFOffset(int32_t value)
{
	Config->setBFOffset(value);
	VFOC->setBFOffset(value);
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
	VFOC->setBrightness(value);
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
	VFOC->softReset();
	VFOC->triggerMemoryWrite();
}

} // namespace VFO
