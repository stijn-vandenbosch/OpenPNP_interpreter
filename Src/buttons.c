/*
 * buttons.c
 *
 *  Created on: 5 dec. 2020
 *      Author: Stijn
 */
/* library includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* my includes */
#include "buttons.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
//https://www.iconarchive.com/show/small-n-flat-icons-by-paomedia/switch-off-icon.html
#include "switch_off_icon_data.h"
//https://www.iconarchive.com/show/small-n-flat-icons-by-paomedia/switch-on-icon.html
#include "switch_on_icon_data.h"

/* defines and macro functions */
#define buttonsINRANGE( xPoint, yPoint, xMin, yMin, xMax, yMax )	( ( ( xPoint ) >= ( xMin ) ) && ( ( xPoint ) <= ( xMax ) ) \
	&& ( ( yPoint ) >= ( yMin ) ) && ( ( yPoint ) <= ( yMax ) ) )

/* static function prototypes */

/* static and external variables */
extern LTDC_HandleTypeDef hltdc;

/*--------------------------------------------------------------------------*/

/*
 * This function draws a button
 */
void vButtonsDraw( ButnStateTypeDef *pxButtonToDraw )
{
	/* only redraw when needed */
	if( !pxButtonToDraw->stateChanged )
		return;

	/* waiting on v-sync before redraw */
	while( !( hltdc.Instance->CDSR & ( 1<<2 ) ) );

	if( pxButtonToDraw->isOn )	//on button
	{
		WDA_LCD_DrawBitmap( SWITCH_ON_ICON_DATA, pxButtonToDraw->startX, pxButtonToDraw->startY, SWITCH_ON_ICON_DATA_X_PIXEL, SWITCH_ON_ICON_DATA_Y_PIXEL, SWITCH_ON_ICON_DATA_FORMAT );
	}
	else	//off button
	{
		WDA_LCD_DrawBitmap( SWITCH_OFF_ICON_DATA, pxButtonToDraw->startX, pxButtonToDraw->startY, SWITCH_OFF_ICON_DATA_X_PIXEL, SWITCH_OFF_ICON_DATA_Y_PIXEL, SWITCH_OFF_ICON_DATA_FORMAT );
	}

	/* new state is drawn */
	pxButtonToDraw->stateChanged = false;
}
/*--------------------------------------------------------------------------*/

/*
 * This function creates a button
 */
ButnStateTypeDef * pxButtonsnewButton( void )
{
ButnStateTypeDef * pxNewButton = NULL;

	/* Allocate memory */
	pxNewButton = (ButnStateTypeDef *)calloc( 1, sizeof( ButnStateTypeDef ) );

	if( pxNewButton == NULL)
	{
		/* Allocation failed */
		return NULL;
	}
	else
	{
		/* Default values */
		pxNewButton->startX = 0;
		pxNewButton->startY = 0;
		pxNewButton->endX = SWITCH_OFF_ICON_DATA_X_PIXEL;
		pxNewButton->endY = SWITCH_OFF_ICON_DATA_Y_PIXEL;
		pxNewButton->isOn = false;
		pxNewButton->stateChanged = true;

		return pxNewButton;
	}
}
/*--------------------------------------------------------------------------*/

/*
 * This function positions the button
 */
void vButtonsSetPosition( ButnStateTypeDef *pxButtonToPosition, uint32_t ulXPos, uint32_t ulYPos )
{
	pxButtonToPosition->startX = ulXPos;
	pxButtonToPosition->startY = ulYPos;
	pxButtonToPosition->endX = ulXPos + SWITCH_OFF_ICON_DATA_X_PIXEL;
	pxButtonToPosition->endY = ulYPos + SWITCH_OFF_ICON_DATA_Y_PIXEL;
}

/*--------------------------------------------------------------------------*/

/*
 * This function checks for button presses and toggles the state accordingly
 */
_Bool bButtonsCheckTouch( ButnStateTypeDef *pxButtonToCheck )
{
TS_StateTypeDef *pxTouchState = NULL;

	BSP_TS_GetState( pxTouchState );

	/* check if a touch occured */
	if( pxTouchState->touchDetected )
	{
		/* check if the touch was in the button range */
		if( buttonsINRANGE( pxTouchState->touchX[0], pxTouchState->touchY[0], pxButtonToCheck->startX, pxButtonToCheck->startY, pxButtonToCheck->endX, pxButtonToCheck->endY ) )
		{
			pxButtonToCheck->isOn = pxButtonToCheck->isOn ? false : true;	//flip state
			pxButtonToCheck->stateChanged = true;
			return true;
		}
	}
	return false;
}
/*--------------------------------------------------------------------------*/
