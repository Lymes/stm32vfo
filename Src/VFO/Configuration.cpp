/*
 * Configuration.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: lymes
 */

#include "Configuration.h"

namespace VFO
{
static Configuration *_sharedInstance = NULL;

Configuration *Configuration::shared()
{
	if (!_sharedInstance)
	{
		_sharedInstance = new Configuration;
	}
	return _sharedInstance;
}

Configuration::Configuration()
{
	_data.frequency = 7100000;
	_data.qFilter1 = 4913811;
	_data.qFilter2 = 4916611;
	_data.bfoOffset = 300;
	_data.calibration = 22334;
	_data.calibrationUin = 8;
	_data.brightness = 255;
}

Configuration::~Configuration()
{
}

void Configuration::save()
{
	if (_mem.isConnected())
	{
		_mem.save((uint8_t *)(&_data), sizeof(_data));
	}
}

void Configuration::load()
{
	if (_mem.isConnected())
	{
		if (!_mem.load((uint8_t *)(&_data), sizeof(_data)))
		{
		}
	}
}

} /* namespace VFO */
