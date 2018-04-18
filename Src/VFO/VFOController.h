/*
 * VFOController.h
 *
 *  Created on: Apr 1, 2018
 *      Author: lymes
 */

#ifndef VFO_VFOCONTROLLER_H_
#define VFO_VFOCONTROLLER_H_

#include "stm32f1xx_hal.h"
#include "GUIController.h"
#include "si5351/si5351.h"
#include "Configuration.h"


namespace VFO
{

class VFOController
{
	Configuration* _conf;
	GUIController* _gui;
	Si5351* _si5351;
	bool _si5351_enabled = true;

public:
	VFOController();
	virtual ~VFOController();
	void begin();

	Configuration *getConfig() { return _conf; }

	void menuKeyPressed();
	void pushEncoderIncrement(int16_t increment, uint16_t period);

	void showSetup();
	void showMain();

	void reset();
	void setFrequency(uint32_t frequency);
	void setBFrequency(uint32_t frequency);
	void setBrightness(uint8_t value);
	void setCalibration(int32_t value);

	void checkMemoryState();
	void triggerMemoryWrite();

	void storeConfiguration();
	void loadConfiguration();
};


} /* namespace VFO */




#endif /* VFO_VFOCONTROLLER_H_ */
