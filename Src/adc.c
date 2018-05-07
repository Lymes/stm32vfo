#include "stm32f1xx_hal.h"

uint16_t readVoltage(ADC_TypeDef *ADCx, uint8_t channel)
{
	uint32_t ADC_value = 0;
	uint32_t voltage = 0;
	if (LL_ADC_IsEnabled(ADCx) == 0)
	{
		/* Enable ADC */
		LL_ADC_Enable(ADCx);
		LL_ADC_StartCalibration(ADCx);
		while ( LL_ADC_IsCalibrationOnGoing(ADCx) ) {}
	}
	/* Select analog input */
	ADCx->SQR3 = channel;
	/* Clear status register */
	LL_ADC_ClearFlag_AWD1(ADCx);
	LL_ADC_ClearFlag_EOS(ADCx);
	LL_ADC_ClearFlag_JEOS(ADCx);
	/* Start Conversion */
	LL_ADC_REG_StartConversionSWStart(ADCx);
	/* Wait for conversion to complete */
	while (!LL_ADC_IsActiveFlag_EOS(ADCx))
	{
	}
	ADC_value = LL_ADC_REG_ReadConversionData12(ADCx);

	static uint32_t oldValue = 0;
	ADC_value = (oldValue * 15 + ADC_value) >> 4;  // cumulative moving average filter
	voltage = (ADC_value * 330) / 4096; /*   calculate voltage   */
	oldValue = ADC_value;

	/* Retrieve result */
	return (uint16_t) voltage;
}
