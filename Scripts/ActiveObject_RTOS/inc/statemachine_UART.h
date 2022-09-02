#ifndef STATEMACHINE_UART_H
#define STATEMACHINE_UART_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

typedef enum {
	STATE_INIT_UART,
	STATE_LISTENING,
	STATE_RECORDING,
	STATE_PROCESSING

} eSystemState_UART;

typedef enum{
	evInit_UART,
	evReceive,
	evHeader,
	evTrailer

} eSystemEvent_UART;

typedef eSystemState_UART (*pfEventHandler_UART)(void);

typedef struct{
	eSystemState_UART 		fsmState;
	eSystemEvent_UART 		fsmEvent;
	pfEventHandler_UART		fsmHandler;
} sStateMachine_UART;

eSystemState_UART 	InitHandler_UART(void);
eSystemState_UART 	Handler_1(void);
eSystemState_UART 	Handler_2(void);


#endif
