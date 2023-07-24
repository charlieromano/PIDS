#ifndef __STATEMACHINE_UART_H__
#define __STATEMACHINE_UART_H__

#include "sapi.h"
#include "board.h"
#include <stdio.h>
#include "displayLed.h"
#include "portmap.h"

#define UART_START_BYTE  	0x78
#define UART_STOP_BYTE  	0xEE
#define UART_BUFFER_LENGTH 	8
#define UART_TIMER_MS 		500	

typedef enum {
	
	STATE_UART_INIT,
	STATE_UART_IDLE,
	STATE_UART_LISTENING,
	STATE_UART_VALID,
	STATE_UART_ERROR

} eSystemState_UART;

typedef enum{
	
	evUart_Init,
	evUart_Received_byte,
	evUart_Timeout

} eSystemEvent_UART;

typedef eSystemState_UART (*pfEventHandler_UART)(void);

typedef struct{

	eSystemState_UART 		fsmState;
	eSystemEvent_UART 		fsmEvent;
	pfEventHandler_UART		fsmHandler;

} sStateMachine_UART;

eSystemState_UART 	uart_initHandler(void);
eSystemState_UART 	uart_idleHandler(void);
eSystemState_UART 	uart_listeningHandler(void);
eSystemState_UART 	uart_processingHandler(void);
eSystemState_UART 	uart_errorHandler(void);

#endif