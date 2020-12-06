/*
 * actuators.c
 *
 *  Created on: 6 dec. 2020
 *      Author: Stijn
 */
/* library includes */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* my includes */
#include "main.h"
#include "buttons.h"
#include "actuators.h"

/* defines and macro's */
#define LIGHT1_ON 801
#define LIGHT1_OFF 802
#define LIGHT2_ON 803
#define LIGHT2_OFF 804
#define LIGHT3_ON 805
#define LIGHT3_OFF 806
#define PUMP_ON 807
#define PUMP_OFF 808
#define VACUUM_ON 809
#define VACUUM_OFF 810
#define FAN_ON 811
#define FAN_OFF 812

/* static function prototypes */

/* static and external variables */
static ButnStateTypeDef *pxPumpButton = NULL;
static ButnStateTypeDef *pxLightButton = NULL;
static ButnStateTypeDef *pxVacuumButton = NULL;


/*--------------------------------------------------------------------------*/

/*
 * This function handles the actuation
 */
void vActuaotrsHandle( uint16_t code )
{
	switch(code)
	{
	case LIGHT1_ON:
		HAL_GPIO_WritePin(LIGHT1_GPIO_Port,LIGHT1_Pin,GPIO_PIN_SET);
		pxLightButton->isOn = true;
		pxLightButton->stateChanged = true;
		break;
	case LIGHT1_OFF:
		HAL_GPIO_WritePin(LIGHT1_GPIO_Port,LIGHT1_Pin,GPIO_PIN_RESET);
		pxLightButton->isOn = false;
		pxLightButton->stateChanged = true;
		break;
	case LIGHT2_ON:
		HAL_GPIO_WritePin(LIGHT2_GPIO_Port,LIGHT2_Pin,GPIO_PIN_SET);
		break;
	case LIGHT2_OFF:
		HAL_GPIO_WritePin(LIGHT2_GPIO_Port,LIGHT2_Pin,GPIO_PIN_RESET);
		break;
	case LIGHT3_ON:
		HAL_GPIO_WritePin(LIGHT3_GPIO_Port,LIGHT3_Pin,GPIO_PIN_SET);
		break;
	case LIGHT3_OFF:
		HAL_GPIO_WritePin(LIGHT3_GPIO_Port,LIGHT3_Pin,GPIO_PIN_RESET);
		break;
	case PUMP_ON:
		HAL_GPIO_WritePin(PUMP_GPIO_Port,PUMP_Pin,GPIO_PIN_SET);
		pxPumpButton->isOn = true;
		pxPumpButton->stateChanged = true;
		break;
	case PUMP_OFF:
		HAL_GPIO_WritePin(PUMP_GPIO_Port,PUMP_Pin,GPIO_PIN_RESET);
		pxPumpButton->isOn = false;
		pxPumpButton->stateChanged = true;
		break;
	case VACUUM_ON:
		HAL_GPIO_WritePin(VACUUM_GPIO_Port,VACUUM_Pin,GPIO_PIN_SET);
		pxVacuumButton->isOn = true;
		pxVacuumButton->stateChanged = true;
		break;
	case VACUUM_OFF:
		HAL_GPIO_WritePin(VACUUM_GPIO_Port,VACUUM_Pin,GPIO_PIN_RESET);
		pxVacuumButton->isOn = false;
		pxVacuumButton->stateChanged = true;
		break;
	case FAN_ON:
		HAL_GPIO_WritePin(FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
		break;
	case FAN_OFF:
		HAL_GPIO_WritePin(FAN_GPIO_Port,FAN_Pin,GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}
/*--------------------------------------------------------------------------*/

/*
 * This function sets pointer to the buttons on screen
 */
void vActuatorsSetButtonHandler( ButnStateTypeDef *pxButtonHandle, ActuatorsEventTypeDef eEvent )
{
	switch( eEvent )
	{
	case ACTUATORS_LIGHTEVENT:
		pxLightButton = pxButtonHandle;
		break;
	case ACTUATORS_PUMPEVENT:
		pxPumpButton = pxButtonHandle;
		break;
	case ACTUATORS_VACUUMEVENT:
		pxVacuumButton = pxButtonHandle;
		break;
	default:
		//invalid event
		break;
	}
}