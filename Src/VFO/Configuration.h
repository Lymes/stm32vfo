/*
 * Configuration.h
 *
 *  Created on: Apr 4, 2018
 *      Author: lymes
 */

#ifndef VFO_CONFIGURATION_H_
#define VFO_CONFIGURATION_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <eeprom/eeprom24xx.h>

#define Config VFO::Configuration::shared()

namespace VFO
{

struct ConfigData {
	uint32_t frequency;
	uint32_t iFrequency;
	uint32_t bFrequency;
	uint32_t encoder;
	int32_t calibration;
	uint8_t brightness;
	int8_t calibrationUin;
};

class Configuration
{
	Eeprom24 _mem;
	ConfigData _data;

public:

	Configuration();
	virtual ~Configuration();

	static Configuration *shared();

	void save();
	void load();

	uint32_t getFrequency(void) { return _data.frequency; }
	int32_t getCalibration(void) { return _data.calibration; }
	int8_t getCalibrationUin(void) { return _data.calibrationUin; }
	uint32_t getIFrequency(void) { return _data.iFrequency; }
	uint32_t getBFrequency(void) { return _data.bFrequency; }
	uint8_t getBrightness(void) { return _data.brightness; }
	uint32_t getEncoder(void) { return _data.encoder; }

	void setFrequency(uint32_t frequency) { _data.frequency = frequency; }
	void setCalibration(uint32_t value) { _data.calibration = value; }
	void setCalibrationUin(int8_t value) { _data.calibrationUin = value; }
	void setIFrequency(uint32_t frequency) { _data.iFrequency = frequency; }
	void setBFrequency(uint32_t frequency) { _data.bFrequency = frequency; }
	void setBrightness(uint8_t value) { _data.brightness = value; }
	void setEncoder(uint32_t value) { _data.encoder = value; }
};

} /* namespace VFO */

#endif /* VFO_CONFIGURATION_H_ */
