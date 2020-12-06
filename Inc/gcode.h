/*
 * gcode.h
 *
 *  Created on: 6 dec. 2020
 *      Author: Stijn
 */

#ifndef GCODE_H_
#define GCODE_H_

typedef enum {
	GCODE_POSITION = 'G',
	GCODE_ACTUATE = 'M'
}GcodeTypeTypeDef;

typedef struct {
	float x;
	float y;
	float z;
	float e;
}GcodeCoordinateTypeDef;

typedef struct {
	GcodeTypeTypeDef type;
	uint16_t code;
	GcodeCoordinateTypeDef position;
}GcodeCommandTypedef;

GcodeCommandTypedef * pxGcodeExtractCommand( char* pcCommandString );
void vGcodeFree( GcodeCommandTypedef *pxCommandToFree );

#endif /* GCODE_H_ */
