#ifndef STATEMACHINE_GPIO_H
#define STATEMACHINE_GPIO_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

/* State Machine GPIO button*/

typedef enum {
	STATE_BUTTON_INIT,
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

eSystemState_button 	buttonInitHandler(void);
eSystemState_button 	bouncingHandler(void);
eSystemState_button 	pushUpHandler(void);
eSystemState_button 	pushDownHandler(void);

#endif
