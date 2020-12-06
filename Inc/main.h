/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f7xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LIGHT2_Pin GPIO_PIN_4
#define LIGHT2_GPIO_Port GPIOB
#define Y_STEP_Pin GPIO_PIN_15
#define Y_STEP_GPIO_Port GPIOA
#define Z_DIR_Pin GPIO_PIN_9
#define Z_DIR_GPIO_Port GPIOB
#define FAN_Pin GPIO_PIN_3
#define FAN_GPIO_Port GPIOI
#define X_STEP_Pin GPIO_PIN_2
#define X_STEP_GPIO_Port GPIOI
#define LCD_BL_CTRL_Pin GPIO_PIN_3
#define LCD_BL_CTRL_GPIO_Port GPIOK
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOI
#define LCD_DISP_Pin GPIO_PIN_12
#define LCD_DISP_GPIO_Port GPIOI
#define Z_STEP_Pin GPIO_PIN_0
#define Z_STEP_GPIO_Port GPIOI
#define BUTTON_Pin GPIO_PIN_11
#define BUTTON_GPIO_Port GPIOI
#define PUMP_Pin GPIO_PIN_8
#define PUMP_GPIO_Port GPIOA
#define LIGHT3_Pin GPIO_PIN_7
#define LIGHT3_GPIO_Port GPIOG
#define LIGHT1_Pin GPIO_PIN_6
#define LIGHT1_GPIO_Port GPIOG
#define VACUUM_Pin GPIO_PIN_6
#define VACUUM_GPIO_Port GPIOH
#define Y_DIR_Pin GPIO_PIN_14
#define Y_DIR_GPIO_Port GPIOB
#define X_DIR_Pin GPIO_PIN_15
#define X_DIR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
