#ifndef STATEMACHINE_IDU_H
#define STATEMACHINE_IDU_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

typedef enum {
	
	STATE_INIT_IDU

} eSystemState_IDU;

typedef enum{

	evIDUInit

} eSystemEvent_IDU;

typedef eSystemState_IDU (*pfEventHandler_IDU)(void);

typedef struct{

	eSystemState_IDU 		fsmState;
	eSystemEvent_IDU 		fsmEvent;
	pfEventHandler_IDU		fsmHandler;

} sStateMachine_IDU;

eSystemState_IDU 	InitHandler_IDU(void);

#endif
