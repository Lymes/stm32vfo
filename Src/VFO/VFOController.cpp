/*
 * VFOController.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#include "VFOController.h"
#include <stdio.h>
#include "stm32f103xb.h"
#include "dwt_stm32_delay.h"

#define delay_us(microseconds) DWT_Delay_us(microseconds)

namespace VFO
{

static VFOController *_sharedInstance;
static uint32_t _timepassed = HAL_GetTick(); // int to hold the STM32 miilis since startup
static int _memStatus = 1;					 // value to notify if memory is current or old. 0=old,

VFOController *VFOController::shared()
{
	if (!_sharedInstance)
	{
		_sharedInstance = new VFOController;
	}
	return _sharedInstance;
}

VFOController::VFOController()
{
	_gui = new GUIController;
	_si5351 = new Si5351;

	VFO::Configuration::shared()->load();
	if (Config->getBrightness() == 0)
	{
		reset();
	}

	this->initSI();
}

void VFOController::initSI()
{
	if (_si5351->init(SI5351_CRYSTAL_LOAD_8PF, 0, 0))
	{
		_si5351->set_correction(Config->getCalibration(), SI5351_PLL_INPUT_XO);
		_si5351->set_freq((_mode == OP_LSB ? (Config->getFrequency() + Config->getQFilter1()) : (Config->getFrequency() + Config->getQFilter2())) * 100, SI5351_CLK0);
		_si5351->set_freq((_mode == OP_LSB ? (Config->getQFilter1() - Config->getBFOffset()) : (Config->getQFilter2() + Config->getBFOffset())) * 100, SI5351_CLK2);
		_si5351->drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA);
		_si5351->drive_strength(SI5351_CLK2, SI5351_DRIVE_2MA);
		_si5351->output_enable(SI5351_CLK1, 0);
	}
	else
	{
		_si5351_enabled = false;
	}
}

VFOController::~VFOController()
{
	delete _gui;
	delete _si5351;
}

void VFOController::begin()
{
	_gui->draw();
	uint8_t brightness = Config->getBrightness();
	for (int i = 0; i < brightness; i++)
	{
		setBrightness(i);
		delay_us(1000);
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

void VFOController::scrollAnimation()
{
	_gui->scrollAnimation();
}

void VFOController::pushEncoderIncrement(int16_t increment, uint16_t period)
{
	_gui->pushEncoderIncrement(increment, period);
}

void VFOController::setFrequency(uint32_t frequency)
{
	if (_si5351_enabled)
	{
		_si5351->set_freq((_mode == OP_LSB ? (frequency + Config->getQFilter1()) : (frequency + Config->getQFilter2())) * 100, SI5351_CLK0);
	}
	Config->setFrequency(frequency);
}

void VFOController::setBFOffset(uint32_t frequency)
{
	if (_si5351_enabled)
	{
		_si5351->set_freq((_mode == OP_LSB ? (Config->getQFilter1() - frequency) : (Config->getQFilter2() + frequency)) * 100, SI5351_CLK2);
	}
}

void VFOController::setQFilter1(uint32_t frequency)
{
	if (_si5351_enabled && _mode == OP_LSB)
	{
		_si5351->set_freq((frequency - Config->getBFOffset()) * 100, SI5351_CLK2);
	}
}

void VFOController::setQFilter2(uint32_t frequency)
{
	if (_si5351_enabled && _mode == OP_USB)
	{
		_si5351->set_freq((frequency + Config->getBFOffset()) * 100, SI5351_CLK2);
	}
}

void VFOController::setBrightness(uint8_t value)
{
	TIM3->CCR1 = value;
}

void VFOController::setCalibration(int32_t value)
{
	if (_si5351_enabled)
	{
		_si5351->set_correction(value, SI5351_PLL_INPUT_XO);
	}
}

void VFOController::storeConfiguration()
{
	Config->save();
}

void VFOController::loadConfiguration()
{
	Config->load();
	setFrequency(Config->getFrequency());
	setCalibration(Config->getCalibration());
	setQFilter1(Config->getQFilter1());
	setQFilter2(Config->getQFilter2());
	setBFOffset(Config->getBFOffset());
	setFrequency(Config->getFrequency());
	setBrightness(Config->getBrightness());
}

void VFOController::softReset()
{
	Config->setFrequency(7125000);
	Config->setCalibration(22334);
	//Config->setCalibration(406000);
	Config->setQFilter1(4913811);
	Config->setQFilter2(4916611);
	Config->setBFOffset(300);
	Config->setBrightness(250);
	Config->setEncoder(128);
	Config->setCalibrationUin(10);

	setFrequency(Config->getFrequency());
	setCalibration(Config->getCalibration());
	setQFilter1(Config->getQFilter1());
	setQFilter2(Config->getQFilter2());
	setBFOffset(Config->getBFOffset());
	setFrequency(Config->getFrequency());
	setBrightness(Config->getBrightness());
}

void VFOController::reset()
{
	this->softReset();
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
		if (_timepassed + 2000 < HAL_GetTick())
		{
			storeConfiguration();
			_memStatus = 1;
		}
	}
}

} /* namespace VFO */
