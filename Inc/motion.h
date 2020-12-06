/*
 * motion.h
 *
 *  Created on: 6 dec. 2020
 *      Author: Stijn
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "gcode.h"

typedef struct{
	uint32_t xSteps;
	_Bool xDir;
	uint32_t ySteps;
	_Bool yDir;
	uint32_t zSteps;
	_Bool zDir;
	uint32_t eSteps;
	_Bool eDir;
}MotionStepsTypeDef;

void vMotionCalculateSteps( GcodeCoordinateTypeDef xStartPosition, GcodeCoordinateTypeDef xMoveToCo );
void vMotionStartMovement( void );

#endif /* MOTION_H_ */
