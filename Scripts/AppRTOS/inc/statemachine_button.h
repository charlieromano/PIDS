#ifndef __STATEMACHINE_BUTTON_H__
#define __STATEMACHINE_BUTTON_H__

#include <stdio.h>
#include "FreeRTOS.h"
#include "sapi.h"
#include "semphr.h"

#define TIMER_MAX_VALUE    256
#define TIMER_MIN_TIMEOUT  3
/*===========================================================================*/
extern SemaphoreHandle_t xMutexUART;
extern SemaphoreHandle_t xBinarySemaphoreUART;
/*===========================================================================*/
extern uint8_t		timer_cnt;
extern bool			timer_flag;
extern gpioMap_t	button;
/*===========================================================================*/
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

#endif
