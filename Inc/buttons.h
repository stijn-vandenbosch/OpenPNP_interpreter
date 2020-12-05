/*
 * buttons.h
 *
 *  Created on: 5 dec. 2020
 *      Author: Stijn
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

/* typedefs */
typedef struct{
	_Bool stateChanged;
	_Bool isOn;
	uint32_t startX;
	uint32_t endX;
	uint32_t startY;
	uint32_t endY;
}ButnStateTypeDef;

/* public function prototypes */
void vButtonsDraw( ButnStateTypeDef *pxButtonToDraw );
ButnStateTypeDef * pxButtonsnewButton( void );
void vButtonsSetPosition( ButnStateTypeDef *pxButtonToPosition, uint32_t ulXPos, uint32_t ulYPos );
_Bool bButtonsCheckTouch( ButnStateTypeDef *pxButtonToCheck );

#endif /* BUTTONS_H_ */
