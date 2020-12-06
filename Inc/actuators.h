/*
 * actuators.h
 *
 *  Created on: 6 dec. 2020
 *      Author: Stijn
 */

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

typedef enum {
	ACTUATORS_PUMPEVENT,
	ACTUATORS_LIGHTEVENT,
	ACTUATORS_VACUUMEVENT
}ActuatorsEventTypeDef;

void vActuatorsHandle( uint16_t code );
void vActuatorsSetButtonHandler( ButnStateTypeDef *pxButtonHandle, ActuatorsEventTypeDef eEvent );

#endif /* ACTUATORS_H_ */
