#ifndef STATEMACHINE_BUTTON_H
#define STATEMACHINE_BUTTON_H

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "sapi.h"
#include "board.h"
#include "task.h"
#include "semphr.h"		
#include "queue.h"      
#include <stdio.h>


#define TIMER_MAX_VALUE    256
#define TIMER_MIN_TIMEOUT  3

typedef enum {
	STATE_BUTTON_INIT,
	STATE_BUTTON_UP,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_RISING
} eSystemState_button;

typedef enum{
	evInit,
	evButtonTimeout,
	evPushed
} eSystemEvent_button;

typedef eSystemState_button (*pfEventHandler_button)(void);

typedef struct{
	eSystemState_button 		fsmState;
	eSystemEvent_button 		fsmEvent;
	pfEventHandler_button 		fsmHandler;
} sStateMachine_button;

eSystemState_button 	buttonInitHandler(void);
eSystemState_button 	bouncingUpHandler(void);
eSystemState_button 	bouncingDownHandler(void);
eSystemState_button 	buttonPushedUpHandler(void);
eSystemState_button 	buttonPushedDownHandler(void);

/* State Machine GPIO button*/
eSystemEvent_button  event_button;
extern gpioMap_t button;
extern uint8_t 	timer_cnt;
extern bool 	timer_flag;
extern QueueHandle_t queueHandle_button;
extern SemaphoreHandle_t xMutexUART;

#endif
