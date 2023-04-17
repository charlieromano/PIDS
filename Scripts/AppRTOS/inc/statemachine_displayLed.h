#ifndef __STATEMACHINE_DISPLAYLED_H__
#define __STATEMACHINE_DISPLAYLED_H__

#include "sapi.h"
#include "board.h"
#include <stdio.h>
#include "displayLed.h"
#include "portmap.h"

typedef enum {
	
	STATE_DISPLAY_INIT,
	STATE_DISPLAY_ENCODING,
	STATE_DISPLAY_LATCH,
	STATE_DISPLAY_OUTPUT_ENABLE,
	STATE_DISPLAY_WAITING,
	STATE_DISPLAY_IDLE

} eSystemState_displayLed;

typedef enum{
	
	evDisplayInit,
	evDisplay_msg_received,
	evDisplay_ready,
	evDisplay_timeout,
	evDisplay_msg_transmited

} eSystemEvent_displayLed;

typedef eSystemState_displayLed (*pfEventHandler_displayLed)(void);

typedef struct{

	eSystemState_displayLed 		fsmState;
	eSystemEvent_displayLed 		fsmEvent;
	pfEventHandler_displayLed		fsmHandler;

} sStateMachine_displayLed;

eSystemState_displayLed 	displayled_initHandler(void);
eSystemState_displayLed 	displayled_dataHandler(void);
eSystemState_displayLed 	displayled_latchHandler(void);
eSystemState_displayLed 	displayled_waitingHandler(void);
eSystemState_displayLed 	displayled_outputHandler(void);



#endif
