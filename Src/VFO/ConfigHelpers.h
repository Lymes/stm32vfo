/*
 * ConfigHelpers.h
 *
 *  Created on: Apr 13, 2018
 *      Author: lymes
 */

#ifndef VFO_CONFIGHELPERS_H_
#define VFO_CONFIGHELPERS_H_

#include "VFOController.h"


extern VFO::VFOController *_mainController;

namespace VFO {

int32_t _getCalibration();
void _setCalibration(int32_t value);

int32_t _getIFrequency();
void _setIFrequency(int32_t value);

int32_t _getBFrequency();
void _setBFrequency(int32_t value);

int32_t _getBrightness();
void _setBrightness(int32_t value);

int32_t _getEncoder();
void _setEncoder(int32_t value);

int32_t _getCalibrationUin();
void _setCalibrationUin(int32_t value);

void _resetConfig(void);

}

#endif /* VFO_CONFIGHELPERS_H_ */
