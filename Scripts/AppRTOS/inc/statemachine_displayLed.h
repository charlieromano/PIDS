#ifndef __STATEMACHINE_DISPLAYLED_H__
#define __STATEMACHINE_DISPLAYLED_H__

#include "sapi.h"
#include "board.h"
#include <stdio.h>
#include "displayLed.h"
#include "portmap.h"

typedef enum {
	
	STATE_DISPLAYLED_INIT,
	STATE_DISPLAYLED_IDLE,
	STATE_DISPLAYLED_PROCESSING,	
	STATE_DISPLAYLED_ENCODING,

} eSystemState_displayLed;

typedef enum{
	
	evDisplayled_init,
	evDisplayled_msg_received,
	evDisplayled_timeout,

} eSystemEvent_displayLed;

typedef eSystemState_displayLed (*pfEventHandler_displayLed)(void);

typedef struct{

	eSystemState_displayLed 		fsmState;
	eSystemEvent_displayLed 		fsmEvent;
	pfEventHandler_displayLed		fsmHandler;

} sStateMachine_displayLed;

eSystemState_displayLed 	displayled_initHandler(void);
eSystemState_displayLed 	displayled_idleHandler(void);
eSystemState_displayLed 	displayled_procHandler(void);
eSystemState_displayLed 	displayled_dataHandler(void);
eSystemState_displayLed 	displayled_latchHandler(void);
eSystemState_displayLed 	displayled_waitingHandler(void);
eSystemState_displayLed 	displayled_outputHandler(void);



#endif
