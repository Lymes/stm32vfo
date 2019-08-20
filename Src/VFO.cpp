#include "VFO.h"

#include "stm32f1xx_hal.h"
#include "VFO/VFOController.h"
#include "kbd/kbd.h"

#define ENC_VALUE 500

VFO::VFOController *_mainController;
volatile uint32_t _ticks = 0;

void _vfoSetup(void);
void _vfoLoopIteration(void);
void _vfoSystick(void);


extern "C"
{
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern uint16_t readVoltage(ADC_TypeDef *ADCx, uint8_t channel);


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
		_mainController->menuKeyPressed();
		//_mainController->initSI();
		break;
	case LONGKEY:
		_mainController->menuKeyPressed();
		break;
	case DOUBLECLICK:
		break;

	}
}


// Initial Setup
void _vfoSetup(void)
{
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_1);
	__HAL_TIM_SET_COUNTER(&htim4, ENC_VALUE);

	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);

	KBD_addKey(GPIOB, 5, LO, KBDCallBack);

	_mainController = new VFO::VFOController;

	if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0 )
	{
		_mainController->reset();
	}
	_mainController->begin();
}


// Loop Iteration
void _vfoLoopIteration(void)
{
	uint16_t encCounter = __HAL_TIM_GET_COUNTER(&htim4);
	if (encCounter != ENC_VALUE)
	{
		__HAL_TIM_SET_COUNTER(&htim4, ENC_VALUE);
		_mainController->pushEncoderIncrement(encCounter - ENC_VALUE, _ticks);
	}
	_ticks = 0;

	uint32_t voltage = readVoltage(ADC1, 3);
	_mainController->showVoltage(voltage);

	_mainController->checkMemoryState();
	HAL_Delay(10);
}


// Tick from sys timer
void _vfoSystick(void)
{
	_ticks++;
}

