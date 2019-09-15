#include "VFO.h"

#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_hal_gpio.h"
#include "VFO/VFOController.h"
#include "dwt_stm32_delay.h"
#include "kbd/kbd.h"
#include "adc.h"

#define ENC_VALUE 500

#define delay_us(microseconds) DWT_Delay_us(microseconds)

volatile uint32_t _ticks = 0;

void _vfoSetup(void);
void _vfoLoopIteration(void);
void _vfoSystick(void);

extern "C"
{
	extern TIM_HandleTypeDef htim3;
	extern TIM_HandleTypeDef htim4;

	void HAL_SYSTICK_Callback(void)
	{
		KBD_ISR_Callback();
	}

	void vfoSetup(void)
	{
		_vfoSetup();
	}

	void vfoLoopIteration(void)
	{
		_vfoLoopIteration();
	}

	void vfoSystick(void)
	{
		_vfoSystick();
	}
}

void KBDCallBack(int key, int action)
{
	switch (action)
	{
	case KEY:
		if (key == 0)
		{
			VFOC->menuKeyPressed();
		}
		else if (key == 1)
		{
			VFOC->invertMode();
		}
		break;
	case LONGKEY:
		if (key == 0)
		{
			VFOC->menuKeyPressed();
		}
		break;
	case DOUBLECLICK:
		break;
	}
}

// Initial Setup
void _vfoSetup(void)
{
	// start TIM4 interrupts
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_1);
	__HAL_TIM_SET_COUNTER(&htim4, ENC_VALUE);

	// start TIM3 interrupts & PWM
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	// init keys
	KBD_addKey(GPIOB, 5, LO, KBDCallBack);
	KBD_addKey(GPIOB, 4, LO, KBDCallBack);

	// start ADC
	LL_ADC_REG_StartConversionSWStart(ADC1);

	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
	{
		VFOC->reset();
	}
	VFOC->begin();
}

// Loop Iteration
void _vfoLoopIteration(void)
{
	uint16_t encCounter = __HAL_TIM_GET_COUNTER(&htim4);
	if (encCounter != ENC_VALUE)
	{
		__HAL_TIM_SET_COUNTER(&htim4, ENC_VALUE);
		VFOC->pushEncoderIncrement(encCounter - ENC_VALUE, _ticks);
	}
	_ticks = 0;

	ADC_values vals;
	readVoltage(ADC1, &vals);
	VFOC->showVoltage(vals.voltage);
	VFOC->showSMeter(vals.s_meter);
	VFOC->checkMemoryState();
	//delay_us(10000);
	HAL_Delay(10);
}

// Tick from sys timer
void _vfoSystick(void)
{
	_ticks++;
}
