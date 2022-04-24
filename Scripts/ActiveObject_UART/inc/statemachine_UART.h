#ifndef STATEMACHINE_UART_H
#define STATEMACHINE_UART_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>
#include "ISR_UART.h"

extern QueueHandle_t dataBuffer;

typedef enum {
	STATE_UART_INIT,
	STATE_LISTENING,
	STATE_RECORDING,
	STATE_PROCESSING

} eSystemState_UART;

typedef enum{
	evUartInit,
	evUartReceive,
	evUartEof

} eSystemEvent_UART;

typedef eSystemState_UART (*pfEventHandler_UART)(void);

typedef struct{
	eSystemState_UART 		fsmState;
	eSystemEvent_UART 		fsmEvent;
	pfEventHandler_UART		fsmHandler;
} sStateMachine_UART;

eSystemState_UART 	InitHandler_UART(void);
eSystemState_UART 	listeningHandler(void);
eSystemState_UART 	recordingHandler(void);
eSystemState_UART 	processingHandler(void);


#endif
