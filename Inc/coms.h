/*
 * coms.h
 *
 *  Created on: 2 dec. 2020
 *      Author: Stijn
 */

#ifndef COMS_H_
#define COMS_H_

void vComsInitListener( void );
void vComsSetNewCommandCallback( void(*callBackFunction)(char *pcData) );
void vComsSetNewClientCallback( void(*callBackFunction)(char *pcIPData) );
void vComsSetConnectionClosedCallback( void(*callBackFunction)(void) );

#endif /* COMS_H_ */
