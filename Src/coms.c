/*
 * coms.c
 *
 *  Created on: 2 dec. 2020
 *      Author: Stijn
 */
/* Library includes */
#include <stdio.h>
#include <stdint.h>
#include <lwip/tcp.h>
#include <lwip/ip4_addr.h>
#include <string.h>

/* my includes */
#include "coms.h"

/* Defines */
#define DEBUG 							//Uncomment this line for debug information on the serial port
#define comsPORT				23		//TCP port to listen on (telnet 23)
#define comsBUFFERSIZE 			64		//Size of commandBuffer
#define comsENDOFCOMMANDCHAR	'\n'	//Command delimiter
#define comsCLOSECONNECTIONCHAR 'X'		//close connection requested

/* Static function prototypes */
#ifdef DEBUG
static void prvComsPrintMyIP(void);
#endif
static err_t prvComsAcceptCallback ( void *arg, struct tcp_pcb *newpcb, err_t err );
static void prvComsErrorCallback( void *arg, err_t err );
static err_t prvComsDataReceivedCallback( void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err );
static void prvCloseConnection( struct tcp_pcb* pxPcbToClose );

/* Static and external variables */
#ifdef DEBUG
extern uint8_t IP_ADDRESS[4];		//initialized in lwip.c
extern ip4_addr_t ipaddr;			//initialized in lwip.c
#endif
static char pcCommandBuffer[comsBUFFERSIZE];	//global buffer to store the received command
static const char *pcResponseString = "ok.\r\n";
static void (*newDataCallback)(char *pcData) = NULL;
static void (*newClientCallback)(char *pcIpString) = NULL;
static void (*connectionClosedCallback)(void) = NULL;

/*--------------------------------------------------------------------------*/

/*
 * This function initializes the listener on the specified TCP port
 * The listening port has to be the same as configured in OpenPNP
 */
void vComsInitListener( void )
{
struct tcp_pcb *pxMyTcpPcb = NULL;	//new pointer to a protocol control block
err_t eBindStatus = ERR_VAL;

	/* create the new listener */
	pxMyTcpPcb = tcp_new();
	eBindStatus = tcp_bind( pxMyTcpPcb, (ip_addr_t*)&ipaddr, (uint16_t)comsPORT );
	pxMyTcpPcb = tcp_listen( pxMyTcpPcb );

	/* specify callback for a new connection */
	tcp_accept( pxMyTcpPcb, prvComsAcceptCallback );

	/* debug information if desired */
#ifdef DEBUG
	printf( "vComsInitListener Dubug:\r\n" );
	switch( eBindStatus )
	{
	case ERR_VAL:
		printf( "*: bind failed because the PCB is not in a valid state\r\n" );
		break;
	case ERR_USE:
		printf( "*: the port %hu is already in use\r\n", (uint16_t)comsPORT );
		break;
	case ERR_OK:
		printf( "*: bound to port %hu on ", (uint16_t)comsPORT );
		prvComsPrintMyIP();
		printf( "\r\n" );
		break;
	default:
		printf( "!: Invalid return type\r\n" );
		break;
	}
#endif
}
/*--------------------------------------------------------------------------*/
#ifdef DEBUG
/*
 * print the local IP address
 */
static void prvComsPrintMyIP( void )
{
	printf( "%hu.%hu.%hu.%hu", (uint16_t)IP_ADDRESS[0], (uint16_t)IP_ADDRESS[1], (uint16_t)IP_ADDRESS[2], (uint16_t)IP_ADDRESS[3] );
}
#endif
/*--------------------------------------------------------------------------*/

/*
 * Called when a new connection can be accepted on a listening pcb.
 */
static err_t prvComsAcceptCallback ( void *arg, struct tcp_pcb *newpcb, err_t err )
{
char pcIpString[64] = "";
	LWIP_UNUSED_ARG( arg );
	LWIP_UNUSED_ARG( err );

	/* set callback functions */
	tcp_err( newpcb, prvComsErrorCallback);
	//tcp_poll( newpcb, NULL, 4 );	//long connection without data is normal, so no callback needed
	tcp_recv( newpcb, prvComsDataReceivedCallback);

	/* construct the 'ipstring' of the remote host and call the newClientCallback */
	sprintf( pcIpString, "%hd.%hd.%hd.%hd", ip4_addr1_16_val( newpcb->remote_ip ), ip4_addr2_16_val( newpcb->remote_ip ), ip4_addr3_16_val( newpcb->remote_ip ), ip4_addr4_16_val( newpcb->remote_ip ) );
	newClientCallback( pcIpString );

	return ERR_OK;
}
/*--------------------------------------------------------------------------*/

/*
 * Called when the pcb receives a RST or is unexpectedly closed for any other reason.
 */
static void prvComsErrorCallback( void *arg, err_t err )
{
	LWIP_UNUSED_ARG( arg );
	LWIP_UNUSED_ARG( err );

#ifdef DEBUG
	printf( "prvComsErrorCallback Debug:\r\n" );
	switch( err )
	{
	case ERR_ABRT:
		printf( "*: aborted through tcp_abort or by a TCP timer\r\n" );
		break;
	case ERR_RST:
		printf( "*: the connection was reset by the remote host\r\n" );
	}
#endif
}
/*--------------------------------------------------------------------------*/

/*
 * Called when data has been received.
 */
static err_t prvComsDataReceivedCallback( void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err )
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
		pcCurrentPayload = (char*)p->payload;
		usTotalLength = p->tot_len;	//store the total length

		pxCurrentBuf = p;			//start with first pbuf

		/*
		 * Check if the first received character is the
		 * 'end of command' character before overwriting
		 * the command buffer
		 */
		if( ( (char*)pxCurrentBuf->payload )[0] == comsENDOFCOMMANDCHAR )
		{
			/* Callback function for main */
			newDataCallback( pcCommandBuffer );

			/* Write a response, no need to copy, responseString is a constant */
			tcp_write( tpcb, pcResponseString, strlen( pcResponseString ), 0);
		}

		/* Loop trough all the pbuf */
		while( pxCurrentBuf->len != pxCurrentBuf->tot_len )
		{
			/* Change the payload pointer */
			pcCurrentPayload = (char*)pxCurrentBuf->payload;

			/* Loop trough the pbuf, j is the index for the current pbuf, i for the commandbuffer */
			for( uint16_t j = 0; ( ( j < pxCurrentBuf->len ) && ( i < comsBUFFERSIZE ) ); i++, j++ )
			{
				pcCommandBuffer[i] = pcCurrentPayload[j];
			}

			/* change the pbuf pointer */
			pxCurrentBuf = pxCurrentBuf->next;
		}

		/* The last one or first one */
		for(  uint16_t j = 0; ( ( j < pxCurrentBuf->len ) && ( i < comsBUFFERSIZE ) ); i++, j++ )
		{
			pcCommandBuffer[i] = pcCurrentPayload[j];
		}

		/* Limit i to prevent an invalid index */
		i = ( i == comsBUFFERSIZE ) ? ( comsBUFFERSIZE - 1 ) : ( i );

		/* Make sure we have a string */
		pcCommandBuffer[i] = '\0';

		/* free the memory -> payload is copied to command buffer */
		pbuf_free( p );

		/* Check for the 'close connection character'
		 * this is for testing purposes
		 */
		if( pcCommandBuffer[0] == comsCLOSECONNECTIONCHAR )
		{
			/* close the connection */
			prvCloseConnection( tpcb );
			connectionClosedCallback();
		}

	}
	/* Other side closed the connection */
	else if( ( err == ERR_OK ) && ( p == NULL ) )
	{
		//close the connection
		prvCloseConnection( tpcb );
		connectionClosedCallback();
	}
	/* Error */
	else
	{
		//free the memory
		pbuf_free( p );
	}

#ifdef DEBUG
	printf( "prvComsDataReceivedCallback Debug:\r\n" );
	if( ( err == ERR_OK ) && ( p != NULL ) )
	{
		printf( "*: received %hu bytes\r\n", usTotalLength );
		printf( "*: buf: %s\r\n",pcCommandBuffer );
	}
	else if( ( err == ERR_OK ) && ( p == NULL ) )
	{
		printf( "*: connection closed\r\n" );
	}
	else
	{
		printf( "!: error\r\n" );
	}
#endif

	return ERR_OK;
}
/*--------------------------------------------------------------------------*/

/*
 * This function closes the connection
 */
static void prvCloseConnection( struct tcp_pcb* pxPcbToClose )
{
	tcp_recv( pxPcbToClose, NULL );	//clear dataReceived callback
	tcp_close( pxPcbToClose );		//close the connection
}
/*--------------------------------------------------------------------------*/

/*
 * This function sets the callback for when new data is received
 */
void vComsSetNewCommandCallback( void(*callBackFunction)(char *pcData) )
{
	newDataCallback = callBackFunction;
}
/*--------------------------------------------------------------------------*/

/*
 * This function sets the callback for when a new client is connected
 * It can be used to display or print the remote IP address
 */
void vComsSetNewClientCallback( void(*callBackFunction)(char *pcIPData) )
{
	newClientCallback = callBackFunction;
}
/*--------------------------------------------------------------------------*/

/*
 * This function sets the callback for when a client disconnects
 * It can be used to clear the remote IP address on the display
 */
void vComsSetConnectionClosedCallback( void(*callBackFunction)(void) )
{
	connectionClosedCallback = callBackFunction;
}
