/*
 * ConfigHelpers.h
 *
 *  Created on: Apr 13, 2018
 *      Author: lymes
 */

#ifndef VFO_CONFIGHELPERS_H_
#define VFO_CONFIGHELPERS_H_

#include "VFOController.h"

namespace VFO
{

int32_t _getCalibration();
void _setCalibration(int32_t value);

int32_t _getQFilter1();
void _setQFilter1(int32_t value);

int32_t _getQFilter2();
void _setQFilter2(int32_t value);

int32_t _getBFOffset();
void _setBFOffset(int32_t value);

int32_t _getBrightness();
void _setBrightness(int32_t value);

int32_t _getEncoder();
void _setEncoder(int32_t value);

int32_t _getCalibrationUin();
void _setCalibrationUin(int32_t value);

void _resetConfig(void);

} // namespace VFO

#endif /* VFO_CONFIGHELPERS_H_ */
