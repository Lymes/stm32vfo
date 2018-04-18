/*
 * Configuration.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: lymes
 */

#include "Configuration.h"


#ifndef EXT_EEPROM
#include "eeprom/eeprom.h"

uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x5000, 0x5001, 0x5002,
0x5003, 0x5004, 0x5005, 0x5006, 0x5007, 0x5008, 0x5009, 0x500a };
#endif



namespace VFO
{

Configuration::Configuration()
{
	// TODO Auto-generated constructor stub
	_data.frequency = 28500000;

#ifndef EXT_EEPROM
	HAL_FLASH_Unlock();
	uint16_t res = EE_Init();
	if ( res == ERASED )
	{
	}
	HAL_FLASH_Lock();
#else
#endif
}

Configuration::~Configuration()
{
}


void Configuration::save()
{
#ifndef EXT_EEPROM
	HAL_FLASH_Unlock();
	EE_WriteVariable(VirtAddVarTab[0], _data.frequency >> 16 );
	EE_WriteVariable(VirtAddVarTab[1], _data.frequency & 0xffff );
	EE_WriteVariable(VirtAddVarTab[2], _data.calibration >> 16 );
	EE_WriteVariable(VirtAddVarTab[3], _data.calibration & 0xffff );
	EE_WriteVariable(VirtAddVarTab[4], _data.iFrequency >> 16 );
	EE_WriteVariable(VirtAddVarTab[5], _data.iFrequency & 0xffff );
	EE_WriteVariable(VirtAddVarTab[6], _data.bFrequency >> 16 );
	EE_WriteVariable(VirtAddVarTab[7], _data.bFrequency & 0xffff );
	uint16_t brightness = _data.brightness;
	EE_WriteVariable(VirtAddVarTab[8], brightness );
	EE_WriteVariable(VirtAddVarTab[9], _data.encoder >> 16 );
	EE_WriteVariable(VirtAddVarTab[10], _data.encoder & 0xffff );
	HAL_FLASH_Lock();
#else
	if ( _mem.isConnected() )
	{
		_mem.save(&_data, sizeof(_data));
	}
#endif
}

void Configuration::load()
{
#ifndef EXT_EEPROM
	uint16_t f1, f2;
	EE_ReadVariable(VirtAddVarTab[0], &f1);
	EE_ReadVariable(VirtAddVarTab[1], &f2);
	_data.frequency = f1 << 16 | f2;
	EE_ReadVariable(VirtAddVarTab[2], &f1);
	EE_ReadVariable(VirtAddVarTab[3], &f2);
	_data.calibration = f1 << 16 | f2;
	EE_ReadVariable(VirtAddVarTab[4], &f1);
	EE_ReadVariable(VirtAddVarTab[5], &f2);
	_data.iFrequency = f1 << 16 | f2;
	EE_ReadVariable(VirtAddVarTab[6], &f1);
	EE_ReadVariable(VirtAddVarTab[7], &f2);
	_data.bFrequency = f1 << 16 | f2;
	uint16_t brightness;
	EE_ReadVariable(VirtAddVarTab[8], &brightness);
	_data.brightness = brightness;
	EE_ReadVariable(VirtAddVarTab[9], &f1);
	EE_ReadVariable(VirtAddVarTab[10], &f2);
	_data.encoder = f1 << 16 | f2;
#else
	if ( _mem.isConnected() )
	{
		_mem.load(&_data, sizeof(_data));
	}
#endif
}

} /* namespace VFO */
