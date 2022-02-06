#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "sapi.h"
#include "board.h"


#include 	<stdio.h>

typedef enum {
	STATE_INIT,
	STATE_A,
	STATE_B,
	STATE_C
} eSystemState;

typedef enum{
	evInit,
	evAlert,
	evReceive,
	evEOF
} eSystemEvent;

typedef eSystemState (*pfEventHandler)(void);

typedef struct{
	eSystemState 		fsmState;
	eSystemEvent 		fsmEvent;
	pfEventHandler 		fsmHandler;
} sStateMachine;

eSystemState 	InitHandler(void)	;
eSystemState 	AlertHandler(void)	;
eSystemState 	ReceiveHandler(void);
eSystemState 	EOFHandler(void) 	;


#endif
