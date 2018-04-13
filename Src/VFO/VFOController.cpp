/*
 * VFOController.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#include "VFOController.h"
#include <stdio.h>

namespace VFO
{

static uint32_t _timepassed = HAL_GetTick(); // int to hold the STM32 miilis since startup
static int _memStatus = 1; // value to notify if memory is current or old. 0=old,

VFOController::VFOController()
{
	_conf = new Configuration;
	_gui = new GUIController;
	_si5351 = new Si5351;
	_conf->load();

	if (_si5351->init(SI5351_CRYSTAL_LOAD_8PF, 0, 0))
	{
		_si5351->set_freq(_conf->getFrequency() * 100, SI5351_CLK0);
	}
	else
	{
		_si5351_enabled = false;
		//_gui->pushEncoderIncrement(-5351);
	}
}

VFOController::~VFOController()
{
	delete _conf;
	delete _gui;
	delete _si5351;
}

void VFOController::begin()
{
	_gui->draw();
}

void VFOController::menuKeyPressed()
{
	_gui->menuKeyPressed();
}

void VFOController::showSetup()
{
	_gui->showSetup();
}

void VFOController::showMain()
{
	_gui->showMain();
}

void VFOController::pushEncoderIncrement(int16_t increment)
{
	_gui->pushEncoderIncrement(increment);
}

void VFOController::setFrequency(uint32_t frequency)
{
	if ( _si5351_enabled )
	{
		_si5351->set_freq(frequency * 100, SI5351_CLK0);
	}
	_conf->setFrequency(frequency);
	triggerMemoryWrite();
}

void VFOController::storeConfiguration()
{
	_conf->save();
}

void VFOController::reset()
{
	_conf->setFrequency(7125000);
	_conf->setCalibration(0);
	_conf->setStep(0);
	_conf->setIFrequency(11500000);
	_conf->setBFrequency(4000000);
	_conf->setBrightness(255);
	_conf->setEncoder(150);
	_conf->save();
	_conf->load();
}

void VFOController::triggerMemoryWrite()
{
	_timepassed = HAL_GetTick();
	_memStatus = 0; // Trigger memory write
}

void VFOController::checkMemoryState()
{
	// Write the frequency to memory if not stored and 2 seconds have passed since the last frequency change.
	if (_memStatus == 0)
	{
		if (_timepassed + 2000 < HAL_GetTick())
		{
			storeConfiguration();
			_memStatus = 1;
		}
	}
}

} /* namespace VFO */
