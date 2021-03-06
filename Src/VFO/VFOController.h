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

#define VFOC VFO::VFOController::shared()

namespace VFO
{

enum OpMode
{
	OP_LSB,
	OP_USB
};

class VFOController
{
	OpMode _mode = OP_LSB;
	GUIController *_gui;
	Si5351 *_si5351;
	bool _si5351_enabled = true;

public:
	static VFOController *shared();

	VFOController();
	virtual ~VFOController();
	void begin();

	void initSI();

	void menuKeyPressed();
	void pushEncoderIncrement(int16_t increment, uint16_t period);

	void showVoltage(uint32_t value);
	void showSMeter(uint32_t value);

	void showSetup();
	void showMain();

	void scrollAnimation();
	void invertMode();
	OpMode opMode() { return _mode; }

	void reset();
	void softReset();
	void setFrequency(uint32_t frequency);

	void setQFilter1(uint32_t frequency);
	void setQFilter2(uint32_t frequency);
	void setBFOffset(uint32_t frequency);

	void setBrightness(uint8_t value);
	void setCalibration(int32_t value);

	void checkMemoryState();
	void triggerMemoryWrite();

	void storeConfiguration();
	void loadConfiguration();
};

} /* namespace VFO */

#endif /* VFO_VFOCONTROLLER_H_ */
