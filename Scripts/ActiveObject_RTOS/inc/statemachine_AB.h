#ifndef STATEMACHINE_AB_H
#define STATEMACHINE_AB_H

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "sapi.h"
#include "board.h"
#include "task.h"
#include "semphr.h"		
#include "queue.h"      
#include <stdio.h>

extern SemaphoreHandle_t xMutexUART;

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
