#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

#define  	HEADER 		1
#define  	TRAILER 	2

extern uint8_t data;

typedef enum {
	STATE_INIT,
	STATE_LISTENING,
	STATE_HEADER,
	STATE_TRAILER
} eSystemState;

typedef enum{
	evInit,
	evReceive,
	evHeader,
	evTrailer
} eSystemEvent;

typedef eSystemState (*pfEventHandler)(void);

typedef struct{
	eSystemState 		fsmState;
	eSystemEvent 		fsmEvent;
	pfEventHandler 		fsmHandler;
} sStateMachine;

eSystemState 	InitHandler(void)		;
eSystemState 	ListeningHandler(void)	;
eSystemState 	HeaderHandler(void)		;
eSystemState 	TrailerHandler(void) 	;


#endif
