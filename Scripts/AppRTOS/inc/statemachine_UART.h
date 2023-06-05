#ifndef __STATEMACHINE_UART_H__
#define __STATEMACHINE_UART_H__

#include "sapi.h"
#include "board.h"
#include <stdio.h>
#include "displayLed.h"
#include "portmap.h"

#define     MAX_BUFFER_SIZE 	2
#define 	DATA_BUFFER_LENGTH 	2
#define 	DATA_ARRAY_LENGTH 	MAX_BUFFER_SIZE*DATA_BUFFER_LENGTH
#define 	MASK_HEADER 		0x7E
#define 	MASK_TRAILER 		0x77

typedef enum {
	
	STATE_UART_INIT,
	STATE_UART_IDLE,
	STATE_UART_LISTENING,
	STATE_UART_DATA,
	STATE_UART_STOP,
	STATE_UART_ERROR

} eSystemState_UART;

typedef enum{
	
	evUart_Init,
	evUart_Rx,
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
eSystemState_UART 	uart_dataHandler(void);
eSystemState_UART 	uart_stopHandler(void);
eSystemState_UART 	uart_errorHandler(void);

#endif