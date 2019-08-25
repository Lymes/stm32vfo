#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"
#include "stm32f1xx_ll_adc.h"
#include <stdint.h>
#include "Configuration.h"

uint16_t readVoltage(ADC_TypeDef *ADCx)
{
	if (LL_ADC_IsEnabled(ADCx) == 0)
	{
		/* Enable ADC */
		LL_ADC_Enable(ADCx);
		//LL_ADC_EnableIT_JEOS(ADCx);
		LL_ADC_StartCalibration(ADCx);
		while (LL_ADC_IsCalibrationOnGoing(ADCx))
		{
		}
	}

	/* Clear status register */
	LL_ADC_ClearFlag_AWD1(ADCx);
	LL_ADC_ClearFlag_EOS(ADCx);
	LL_ADC_ClearFlag_JEOS(ADCx);
	/* Start Injected Conversion */
	LL_ADC_INJ_StartConversionSWStart(ADCx);
	/* Wait for conversion to complete */
	while (!LL_ADC_IsActiveFlag_JEOS(ADCx))
	{
	}

	uint32_t ADC_value = LL_ADC_INJ_ReadConversionData12(ADCx, LL_ADC_INJ_RANK_1);
	uint32_t REF_value = LL_ADC_INJ_ReadConversionData12(ADCx, LL_ADC_INJ_RANK_2);

	static uint32_t oldValue = 0;
	uint32_t voltage = (116 * 12 * ADC_value) / REF_value; /*   calculate voltage   */
	voltage = (oldValue * 15 + voltage) >> 4;			   // cumulative moving average filter
	oldValue = voltage;

	return voltage;
}
