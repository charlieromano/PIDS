#ifndef STATEMACHINE_LDU_H
#define STATEMACHINE_LDU_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

typedef enum {
	
	STATE_INIT_LDU

} eSystemState_LDU;

typedef enum{

	evLDUInit

} eSystemEvent_LDU;

typedef eSystemState_LDU (*pfEventHandler_LDU)(void);

typedef struct{

	eSystemState_LDU 		fsmState;
	eSystemEvent_LDU 		fsmEvent;
	pfEventHandler_LDU		fsmHandler;

} sStateMachine_LDU;

eSystemState_LDU 	InitHandler_LDU(void);

#endif
