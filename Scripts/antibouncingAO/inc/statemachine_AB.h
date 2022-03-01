#ifndef STATEMACHINE_AB_H
#define STATEMACHINE_AB_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

typedef enum {
	STATE_INIT_AB,
	STATE_A,
	STATE_B
} eSystemState_AB;

typedef enum{
	evInit_AB,
	evTimeout_A,
	evTimeout_B
} eSystemEvent_AB;

typedef eSystemState_AB (*pfEventHandler_AB)(void);

typedef struct{
	eSystemState_AB 		fsmState;
	eSystemEvent_AB 		fsmEvent;
	pfEventHandler_AB		fsmHandler;
} sStateMachine_AB;

eSystemState_AB 	InitHandler_AB(void);
eSystemState_AB 	AtoBHandler(void);
eSystemState_AB 	BtoAHandler(void);


#endif
