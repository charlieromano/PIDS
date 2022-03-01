#ifndef STATEMACHINE_BUTTON_H
#define STATEMACHINE_BUTTON_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>


typedef enum {
	STATE_BUTTON_DOWN,
	STATE_BUTTON_UP,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING
} eSystemState_button;

typedef enum{
	evBouncing,
	evPushed
} eSystemEvent_button;

typedef eSystemState_button (*pfEventHandler_button)(void);

typedef struct{
	eSystemState_button 		fsmState;
	eSystemEvent_button 		fsmEvent;
	pfEventHandler_button 		fsmHandler;
} sStateMachine_button;

eSystemState_button 	bouncingUpHandler(void);
eSystemState_button 	bouncingDownHandler(void);
eSystemState_button 	pushingUpHandler(void);
eSystemState_button 	pushingDownHandler(void);


#endif
