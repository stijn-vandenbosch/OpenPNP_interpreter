/*
 * motion.c
 *
 *  Created on: 6 dec. 2020
 *      Author: Stijn
 */
/* library includes */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* my includes */
#include "motion.h"
#include "main.h"

/* defines and macro's */
#define motionSTEPSPERMM 	50	//adjust this value as needed
//#define REVERSE			//uncomment to reverse directions
#define motionAXISCOUNT	4	//number of system axis

/* static function prototypes */

/* static and external variables */
static uint8_t ucAxisToComplete = motionAXISCOUNT;
static MotionStepsTypeDef xCalculatedSteps = {0,false,0,false,0,false,0,false};
extern TIM_HandleTypeDef htim4;

/*--------------------------------------------------------------------------*/

/*
 * This function calculates the required steps
 */
void vMotionCalculateSteps( GcodeCoordinateTypeDef xStartPosition, GcodeCoordinateTypeDef xMoveToCo )
{
	/* x-axis */
	if( xMoveToCo.x > xStartPosition.x )
	{
		xCalculatedSteps.xSteps = ( xMoveToCo.x - xStartPosition.x ) * motionSTEPSPERMM;
		xCalculatedSteps.xDir = 1;
	}
	else
	{
		xCalculatedSteps.xSteps = ( xStartPosition.x - xMoveToCo.x ) * motionSTEPSPERMM;
		xCalculatedSteps.xDir = 0;
	}

	/* y-axis */
	if( xMoveToCo.y > xStartPosition.y )
	{
		xCalculatedSteps.ySteps = ( xMoveToCo.y - xStartPosition.y ) * motionSTEPSPERMM;
		xCalculatedSteps.yDir = 1;
	}
	else
	{
		xCalculatedSteps.ySteps = ( xStartPosition.y - xMoveToCo.y ) * motionSTEPSPERMM;
		xCalculatedSteps.yDir = 0;
	}

	/* z-axis */
	if( xMoveToCo.z > xStartPosition.z )
	{
		xCalculatedSteps.zSteps = ( xMoveToCo.z - xStartPosition.z ) * motionSTEPSPERMM;
		xCalculatedSteps.zDir = 1;
	}
	else
	{
		xCalculatedSteps.zSteps = ( xStartPosition.z - xMoveToCo.z ) * motionSTEPSPERMM;
		xCalculatedSteps.zDir = 0;
	}

	#ifdef REVERSE
		steps->xDir = !steps->xDir;
		steps->yDir = !steps->yDir;
		steps->zDir = !steps->zDir;
	#endif
}
/*--------------------------------------------------------------------------*/

/*
 * This function starts the movement and waits for completion
 */
void vMotionStartMovement( void )
{
	/* Set the direction pins */
	HAL_GPIO_WritePin( X_DIR_GPIO_Port, X_DIR_Pin, (GPIO_PinState)xCalculatedSteps.xDir );
	HAL_GPIO_WritePin( Y_DIR_GPIO_Port, Y_DIR_Pin, (GPIO_PinState)xCalculatedSteps.yDir );
	HAL_GPIO_WritePin( Z_DIR_GPIO_Port, Z_DIR_Pin, (GPIO_PinState)xCalculatedSteps.zDir );
	HAL_GPIO_WritePin( E_DIR_GPIO_Port, E_DIR_Pin, (GPIO_PinState)xCalculatedSteps.eDir );

	/* Set the remaining axis to complete */
	ucAxisToComplete = motionAXISCOUNT;

	/* Activate the step channels */
	HAL_TIM_PWM_Start_IT( &htim4, TIM_CHANNEL_1 );
	HAL_TIM_PWM_Start_IT( &htim4, TIM_CHANNEL_2 );
	HAL_TIM_PWM_Start_IT( &htim4, TIM_CHANNEL_3 );
	HAL_TIM_PWM_Start_IT( &htim4, TIM_CHANNEL_4 );

	/* Wait for completion */
	while( ucAxisToComplete > 0 );
}
/*--------------------------------------------------------------------------*/

/*
 * Overwritten interrupt callback function
 * 4 Independent timer channels represent the 4 axis
 * In order to alter the step frequency, the PWM frequency needs to be changed
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	switch( htim->Channel )
	{
	case HAL_TIM_ACTIVE_CHANNEL_1:
		if( xCalculatedSteps.xSteps > 0 )
		{
			HAL_GPIO_WritePin(X_STEP_GPIO_Port,X_STEP_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(X_STEP_GPIO_Port,X_STEP_Pin,GPIO_PIN_RESET);
			xCalculatedSteps.xSteps--;
		}
		else
		{
			HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_1);
			ucAxisToComplete--;
		}
		break;
	case HAL_TIM_ACTIVE_CHANNEL_2:
		if( xCalculatedSteps.ySteps > 0 )
		{
			HAL_GPIO_WritePin(Y_STEP_GPIO_Port,Y_STEP_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Y_STEP_GPIO_Port,Y_STEP_Pin,GPIO_PIN_RESET);
			xCalculatedSteps.ySteps--;
		}
		else
		{
			HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_2);
			ucAxisToComplete--;
		}
		break;
	case HAL_TIM_ACTIVE_CHANNEL_3:
		if( xCalculatedSteps.zSteps > 0 )
		{
			HAL_GPIO_WritePin(Z_STEP_GPIO_Port,Z_STEP_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Z_STEP_GPIO_Port,Z_STEP_Pin,GPIO_PIN_RESET);
			xCalculatedSteps.zSteps--;
		}
		else
		{
			HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_3);
			ucAxisToComplete--;
		}
		break;
	case HAL_TIM_ACTIVE_CHANNEL_4:
		if( xCalculatedSteps.eSteps > 0 )
		{
			HAL_GPIO_WritePin(E_STEP_GPIO_Port,E_STEP_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_STEP_GPIO_Port,E_STEP_Pin,GPIO_PIN_RESET);
			xCalculatedSteps.eSteps--;
		}
		else
		{
			HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_4);
			ucAxisToComplete--;
		}
		break;
	default:
		//invalid channel
		break;
	}
}
