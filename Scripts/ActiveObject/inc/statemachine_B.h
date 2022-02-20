#ifndef STATEMACHINE_B_H
#define STATEMACHINE_B_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

extern uint8_t data;

typedef enum {
	STATE_INIT_B,
	STATE_A,
	STATE_B
} eSystemState_B;

typedef enum{
	evInit_B,
	evTimeout1,
	evTimeout2
} eSystemEvent_B;

typedef eSystemState_B (*pfEventHandler_B)(void);

typedef struct{
	eSystemState_B 		fsmState;
	eSystemEvent_B 		fsmEvent;
	pfEventHandler_B	fsmHandler;
} sStateMachine_B;

eSystemState_B 	InitHandler_B(void);
eSystemState_B 	AtoBHandler(void);
eSystemState_B 	BtoAHandler(void);


#endif
