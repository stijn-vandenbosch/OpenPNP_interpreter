/*
 * gcode.c
 *
 *  Created on: 6 dec. 2020
 *      Author: Stijn
 */
/* library includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>

/* my includes */
#include "gcode.h"

/* defines and macro's */
//#define DEBUG	//uncomment to enable debug
#define gcodeNEEDCOORDINATE( type, code ) \
	( ( type == GCODE_POSITION ) && ( ( code == 0 ) || ( code == 1 ) ) )

/* static function prototypes */
static void prvGcodeGetXYZE( char* pcStringToSearch, GcodeCoordinateTypeDef *pxCurrentPos );

/* static and external variables */

/*--------------------------------------------------------------------------*/

/*
 * This function tries to extract a g-code command from a string
 * returns a pointer to the extracted command
 * returns NULL when an invalid command is received or when memory could not be allocated
 */
GcodeCommandTypedef * pxGcodeExtractCommand( char* pcCommandString, GcodeCoordinateTypeDef xCurrentPosition )
{
GcodeCommandTypedef *pxNewCommand = NULL;
char cFirstChar = pcCommandString[0];

	/* Allocate memory for the new command */
	pxNewCommand = (GcodeCommandTypedef *)calloc( 1, sizeof( GcodeCommandTypedef ) );
	if(pxNewCommand == NULL)
	{
#ifdef DEBUG
		malloc_stats();
#endif
		/* Could not allocate memory */
		return pxNewCommand;
	}

	/* Get the type */
	if( ( (GcodeTypeTypeDef)cFirstChar != GCODE_ACTUATE ) && ( (GcodeTypeTypeDef)cFirstChar != GCODE_POSITION ) )
	{
#ifdef DEBUG
		printf( "Invalid type %c\r\n", cFirstChar);
#endif
		/* Invalid type */
		return pxNewCommand;
	}
	pxNewCommand->type = (GcodeTypeTypeDef)cFirstChar;
#ifdef DEBUG
	printf( "Type: %c\r\n", cFirstChar );
#endif

	/* Get the code which comes after the type */
	sscanf( ( ++pcCommandString ), "%hu", &( pxNewCommand->code ) );
#ifdef DEBUG
	printf( "Code: %hu\r\n", pxNewCommand->code );
#endif

	/* Based on the type we need to read an additional coordinate */
	if( gcodeNEEDCOORDINATE( pxNewCommand->type, pxNewCommand->code ) )
	{
		/* preload the coordinate in order to save the previous state when an axis is not specified.
		 * example: current x:100 y:200 e:30 received x:50 y:40 -> e needs to stay 30.
		 * Because calloc sets all memory locations to 0, requested e will be 0 -> incorrect
		 * This is why we preload with the previous coordinate
		 */
		vGcodeCopyCo( &(pxNewCommand->position), xCurrentPosition );

		prvGcodeGetXYZE( pcCommandString, &( pxNewCommand->position ) );
	}

	/* return the command */
	return pxNewCommand;

}
/*--------------------------------------------------------------------------*/

/*
 * This function extracts a coordinate from the command string
 * -u _scanf_float must be added to linker flags
 */
static void prvGcodeGetXYZE( char* pcStringToSearch, GcodeCoordinateTypeDef *pxCoordintate )
{
char * pcIndexOfChar = NULL;
	/* find x */
	pcIndexOfChar = strchr( pcStringToSearch,'X' );
	if( pcIndexOfChar )
	{
		pcIndexOfChar++;
		sscanf( pcIndexOfChar, "%f", &( pxCoordintate->x ) );
	}
	/* find y */
	pcIndexOfChar = strchr( pcStringToSearch,'Y' ); //find y
	if( pcIndexOfChar )
	{
		pcIndexOfChar++;
		sscanf( pcIndexOfChar, "%f", &( pxCoordintate->y ) );
	}
	/* find z */
	pcIndexOfChar = strchr(pcStringToSearch,'Z'); //find y
	if( pcIndexOfChar )
	{
		pcIndexOfChar++;
		sscanf( pcIndexOfChar, "%f", &( pxCoordintate->z ) );
	}
	/* find e */
	pcIndexOfChar = strchr(pcStringToSearch,'E'); //find e
	if( pcIndexOfChar )
	{
		pcIndexOfChar++;
		sscanf( pcIndexOfChar, "%f", &( pxCoordintate->e ) );
	}
}
/*--------------------------------------------------------------------------*/

/*
 * This function clears a Gcode command when completed
 */
void vGcodeFree( GcodeCommandTypedef *pxCommandToFree )
{
	free( pxCommandToFree );
}
/*--------------------------------------------------------------------------*/

/*
 * This function copy's coordinates
 */
void vGcodeCopyCo( GcodeCoordinateTypeDef *pxDestination, GcodeCoordinateTypeDef xSource )
{
	pxDestination->x = xSource.x;
	pxDestination->y = xSource.y;
	pxDestination->z = xSource.z;
	pxDestination->e = xSource.e;
}

