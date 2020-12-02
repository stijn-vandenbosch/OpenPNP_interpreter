/*
 * coms.c
 *
 *  Created on: 2 dec. 2020
 *      Author: Stijn
 */
#include <stdio.h>
#include <lwip/tcp.h>
#include <lwip/ip4_addr.h>

#include "coms.h"

#define DEBUG 		//Uncomment this line for debug information on the serial port
#define PORT	23	//TCP port to listen on


static void prvComsPrintMyIP(void);
static void prvComsAcceptCallback (void *arg, struct tcp_pcb *newpcb, err_t err);

extern uint8_t IP_ADDRESS[4];	//initialized in lwip.c
extern ip4_addr_t ipaddr;
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
	eBindStatus = tcp_bind(pxMyTcpPcb, &ipaddr, (uint16_t)PORT);
	pxMyTcpPcb = tcp_bind(pxMyTcpPcb);

	/* specify callback */
	tcp_accept(pxMyTcpPcb, prvComsAcceptCallback);

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

static void prvComsAcceptCallback (void *arg, struct tcp_pcb *newpcb, err_t err)
{

}
