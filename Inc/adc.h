#ifndef __ADC_H
#define __ADC_H

#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"
#include "stm32f1xx_ll_adc.h"
#include <stdint.h>

struct ADC_values
{
    uint16_t voltage;
    uint16_t s_meter;
};

void readVoltage(ADC_TypeDef *ADCx, struct ADC_values *values);

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
