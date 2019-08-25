/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_dma.h"

#include "stm32f1xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TFT_LED_Pin GPIO_PIN_6
#define TFT_LED_GPIO_Port GPIOA
#define I2C2_SCL_Pin GPIO_PIN_10
#define I2C2_SCL_GPIO_Port GPIOB
#define I2C2_SDA_Pin GPIO_PIN_11
#define I2C2_SDA_GPIO_Port GPIOB
#define TFT_A0_Pin GPIO_PIN_9
#define TFT_A0_GPIO_Port GPIOA
#define TFT_RESET_Pin GPIO_PIN_10
#define TFT_RESET_GPIO_Port GPIOA
#define TFT_CS_Pin GPIO_PIN_12
#define TFT_CS_GPIO_Port GPIOA
#define BTN_STP_Pin GPIO_PIN_5
#define BTN_STP_GPIO_Port GPIOB
#define ENC1_Pin GPIO_PIN_6
#define ENC1_GPIO_Port GPIOB
#define ENC2_Pin GPIO_PIN_7
#define ENC2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define STM32F103C8 // board type definition

#define GET_MACRO(_0, _1, NAME, ...) NAME
#define Error_Handler(...) GET_MACRO(_0, ##__VA_ARGS__, Error_Handler1, Error_Handler0) \
()
#define Error_Handler0() _Error_Handler((char *)__FILE__, __LINE__)
#define Error_Handler1(unused) _Error_Handler(char *file, int line)

  extern void _Error_Handler(char *, int);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
