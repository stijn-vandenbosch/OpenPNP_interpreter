/*
 * coms.c
 *
 *  Created on: 2 dec. 2020
 *      Author: Stijn
 */
/* Library includes */
#include <stdio.h>
#include <lwip/tcp.h>
#include <lwip/ip4_addr.h>
#include <string.h>

/* my includes *
#include "coms.h"

/* Defines */
#define DEBUG 					//Uncomment this line for debug information on the serial port
#define PORT				23	//TCP port to listen on (telnet 23)
#define BUFFERSIZE 			64	//Size of commandBuffer
#define ENDOFCOMMANDCHAR	'\n'//Command delimiter
#define CLOSECONNECTIONCHAR 'X'	//close connection requested

/* Static function prototypes */
static void prvComsPrintMyIP(void);
static err_t prvComsAcceptCallback (void *arg, struct tcp_pcb *newpcb, err_t err);
static void prvComsErrorCallback(void *arg, err_t err);
static err_t prvComsDataReceivedCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void prvCloseConnection( struct tcp_pcb* pxPcbToClose);

/* Static and external variables */
extern uint8_t IP_ADDRESS[4];		//initialized in lwip.c
extern ip4_addr_t ipaddr;			//initialized in lwip.c
static char cCommandbuffer[BUFFERSIZE];	//global buffer to store the received command
static const char *pcResponseString = "ok.\r\n";
static void (*newDataCallback)(char *pcData) = NULL;

/*--------------------------------------------------------------------------*/

/*
 * This function initializes the listener on the specified TCP port
 * The listening port has to be the same as configured in OpenPNP
 */
void vComsInitListener(void)
{
struct tcp_pcb *pxMyTcpPcb = NULL;	//new pointer to a protocol control block
err_t eBindStatus = ERR_VAL;

	/* create the new listener */
	pxMyTcpPcb = tcp_new();
	eBindStatus = tcp_bind( pxMyTcpPcb, &ipaddr, (uint16_t)PORT );
	pxMyTcpPcb = tcp_listen( pxMyTcpPcb );

	/* specify callback */
	tcp_accept( pxMyTcpPcb, prvComsAcceptCallback );

	/* debug information if desired */
#ifdef DEBUG
	printf("vComsInitListener Dubug:\r\n");
	switch(eBindStatus)
	{
	case ERR_VAL:
		printf("*: bind failed because the PCB is not in a valid state\r\n");
		break;
	case ERR_USE:
		printf("*: the port %hd is already in use\r\n",(uint16_t)PORT);
		break;
	case ERR_OK:
		printf("*: bound to port %hd on ",(uint16_t)PORT);
		prvComsPrintMyIP();
		printf("\r\n");
		break;
	default:
		printf("!: Invalid return type\r\n");
		break;
	}
#endif
}
/*--------------------------------------------------------------------------*/

/*
 * print the local IP address
 */
static void prvComsPrintMyIP(void)
{
	printf("%hd.%hd.%hd.%hd",(uint16_t)IP_ADDRESS[0],(uint16_t)IP_ADDRESS[1],(uint16_t)IP_ADDRESS[2],(uint16_t)IP_ADDRESS[3]);
}
/*--------------------------------------------------------------------------*/

/*
 * Called when a new connection can be accepted on a listening pcb.
 */
static err_t prvComsAcceptCallback (void *arg, struct tcp_pcb *newpcb, err_t err)
{
	LWIP_UNUSED_ARG( arg );
	LWIP_UNUSED_ARG( err );

	/* set callback functions */
	tcp_err( newpcb, prvComsErrorCallback);
	tcp_poll( newpcb, NULL, 4 );	//TODO: add callback
	tcp_recv( newpcb, prvComsDataReceivedCallback);

	return ERR_OK;
}
/*--------------------------------------------------------------------------*/

/*
 * Called when the pcb receives a RST or is unexpectedly closed for any other reason.
 */
static void prvComsErrorCallback(void *arg, err_t err)
{
	LWIP_UNUSED_ARG( arg );
	LWIP_UNUSED_ARG( err );

#ifdef DEBUG
	printf("prvComsErrorCallback Debug:\r\n");
	switch(err)
	{
	case ERR_ABRT:
		printf("*: aborted through tcp_abort or by a TCP timer\r\n");
		break;
	case ERR_RST:
		printf("*: the connection was reset by the remote host\r\n");
	}
#endif
}
/*--------------------------------------------------------------------------*/

/*
 * Called when data has been received.
 */
static err_t prvComsDataReceivedCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
uint16_t i = 0;
struct pbuf* pxCurrentBuf = NULL;
uint16_t usTotalLength = 0;
char *pcCurrentPayload = NULL;

	LWIP_UNUSED_ARG( arg );

	/* New data */
	if( ( err == ERR_OK ) && ( p != NULL ) )
	{
		tcp_recved( tpcb, p->tot_len ); //ack packet

		/* Payload handling starts here */
		usTotalLength = p->tot_len;	//store the total length

		pxCurrentBuf = p;			//start with first pbuf
		i = 0;						//Initialize the commandbuffer index with 0

		/*
		 * Check if the first received character is the
		 * 'end of command' character before overwriting
		 * the command buffer
		 */
		if( ( (char*)pxCurrentBuf->payload[0] ) == ENDOFCOMMANDCHAR )
		{
			/* Write a response, no need to copy */
			tcp_write( tpcb, pcResponseString, strlen( pcResponseString ), 0);

			/* Callback function for main */
			newDataCallback( cCommandbuffer );
		}

		/* Loop trough all the pbuf */
		while( pxCurrentBuf->len != pxCurrentBuf->tot_len )
		{
			/* Change the payload pointer */
			pcCurrentPayload = pxCurrentBuf->payload;

			/* Loop trough the pbuf, j is the index for the current pbuf, i for the commandbuffer */
			for( uint16_t j = 0; ( ( j < pxCurrentBuf->len ) && ( i < BUFFERSIZE ) ); i++, j++ )
			{
				cCommandbuffer[i] = pcCurrentPayload[j];
			}

			/* change the pbuf pointer */
			pxCurrentBuf = pxCurrentBuf->next;
		}

		/* The last one or first one */
		for(  uint16_t j = 0; ( ( j < pxCurrentBuf->len ) && ( i < BUFFERSIZE ) ); i++, j++ )
		{
			cCommandbuffer[i] = pcCurrentPayload[j];
		}

		/* Limit i to prevent an invalid index */
		i = ( i == BUFFERSIZE ) ? ( BUFFERSIZE - 1 ) : ( i );

		/* Make sure we have a string */
		cCommandbuffer[i] = '\0';

		/* free the memory -> payload is copied to commandbuffer */
		pbuf_free( p );

		/* Check for the 'close connection character' */
		if( cCommandbuffer[0] == CLOSECONNECTIONCHAR )
		{
			/* close the connection */
			prvCloseConnection( tpcb );
		}
		else
		{
			/* normal command */
		}


	}
	/* Other side closed the connection */
	else if( ( err == ERR_OK ) && ( p == NULL ) )
	{
		//close the connection
		prvCloseConnection( tpcb );
	}
	/* Error */
	else
	{
		//free the memory
		pbuf_free( p );
	}

#ifdef DEBUG
	printf("prvComsDataReceivedCallback Debug:\r\n");
	if( ( err == ERR_OK ) && ( p != NULL ) )
	{
		printf("*: received %hd bytes\r\n",usTotalLength);
		printf("*: buf: %s\r\n",cCommandbuffer);
	}
	else if( ( err == ERR_OK ) && ( p == NULL ) )
	{
		printf("*: connection closed\r\n");
	}
	else
	{
		printf("!: error\r\n");
	}
#endif

	return ERR_OK;
}
/*--------------------------------------------------------------------------*/

/*
 * This function closes the connection
 */
static void prvCloseConnection( struct tcp_pcb* pxPcbToClose)
{
	tcp_recv( pxPcbToClose, NULL );	//clear dataReceived callback
	tcp_close( pxPcbToClose );		//close the connection
}
/*--------------------------------------------------------------------------*/

/*
 * This function sets the callback for when new data is received
 */
void vSetNewCommandCallback(void(*callBackFunction)(char *pcData))
{
	newDataCallback = callBackFunction;
}
