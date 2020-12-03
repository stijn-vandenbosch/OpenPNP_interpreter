/*
 * coms.h
 *
 *  Created on: 2 dec. 2020
 *      Author: Stijn
 */

#ifndef COMS_H_
#define COMS_H_

void vComsInitListener(void);
void vSetNewCommandCallback(void(*callBackFunction)(char *pcData));

#endif /* COMS_H_ */
