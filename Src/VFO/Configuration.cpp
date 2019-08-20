/*
 * Configuration.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: lymes
 */

#include "Configuration.h"

namespace VFO
{

Configuration::Configuration()
{
	// TODO Auto-generated constructor stub
	_data.frequency   = 7100000;
	_data.iFrequency  = 4000000;
	_data.bFrequency  = 4000000;
	_data.calibration = 22334;
	_data.brightness  = 255;
}

Configuration::~Configuration()
{
}


void Configuration::save()
{
	if ( _mem.isConnected() )
	{
		_mem.save((uint8_t *)(&_data), sizeof(_data));
	}
}


void Configuration::load()
{
	if ( _mem.isConnected() )
	{
		if ( !_mem.load((uint8_t *)(&_data), sizeof(_data)) )
		{

		}
	}
}

} /* namespace VFO */
