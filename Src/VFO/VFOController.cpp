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
	if ( _conf->getBrightness() == 0 )
	{
		reset();
	}

	if (_si5351->init(SI5351_CRYSTAL_LOAD_8PF, 0, 0))
	{
		_si5351->set_correction(_conf->getCalibration(), SI5351_PLL_INPUT_XO);
		_si5351->set_freq(_conf->getFrequency()  * 100, SI5351_CLK0);
		_si5351->set_freq(_conf->getBFrequency() * 100, SI5351_CLK1);
		_si5351->output_enable(SI5351_CLK2, 0);
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
	for ( int i = 0; i < _conf->getBrightness(); i++ )
	{
		setBrightness(i);
		HAL_Delay(1);
	}
}

void VFOController::menuKeyPressed()
{
	_gui->menuKeyPressed();
}

void VFOController::showVoltage(uint32_t value)
{
	_gui->showVoltage(value);
}

void VFOController::showSetup()
{
	_gui->showSetup();
}

void VFOController::showMain()
{
	_gui->showMain();
}

void VFOController::pushEncoderIncrement(int16_t increment, uint16_t period)
{
	_gui->pushEncoderIncrement(increment, period);
}

void VFOController::setFrequency(uint32_t frequency)
{
	if ( _si5351_enabled )
	{
		_si5351->set_freq(frequency * 100 * 4, SI5351_CLK0);
	}
	_conf->setFrequency(frequency);
}

void VFOController::setBFrequency(uint32_t frequency)
{
	if ( _si5351_enabled )
	{
		_si5351->set_freq(frequency * 100, SI5351_CLK1);
	}
}

void VFOController::setBrightness(uint8_t value)
{
	TIM3->CCR1 = value;
}

void VFOController::setCalibration(int32_t value)
{
	if ( _si5351_enabled )
	{
		_si5351->set_correction(value, SI5351_PLL_INPUT_XO);
	}
}

void VFOController::storeConfiguration()
{
	_conf->save();
}


void VFOController::loadConfiguration()
{
	_conf->load();
	setFrequency(_conf->getFrequency());
	setCalibration(_conf->getCalibration());
	setBFrequency(_conf->getBFrequency());
	setFrequency(_conf->getFrequency());
	setBrightness(_conf->getBrightness());
}


void VFOController::reset()
{
	_conf->setFrequency(7125000);
	//_conf->setCalibration(27000);
	_conf->setCalibration(406000);
	_conf->setIFrequency(11500000);
	_conf->setBFrequency(4000000);
	_conf->setBrightness(255);
	_conf->setEncoder(128);
	storeConfiguration();
	loadConfiguration();
}

void VFOController::triggerMemoryWrite()
{
	_timepassed = HAL_GetTick();
	_memStatus = 0; // Trigger memory write
}

void VFOController::checkMemoryState()
{
	// Write the frequency to memory if not stored and 3 seconds have passed since the last frequency change.
	if (_memStatus == 0)
	{
		if (_timepassed + 3000 < HAL_GetTick())
		{
			storeConfiguration();
			_memStatus = 1;
		}
	}
}

} /* namespace VFO */
