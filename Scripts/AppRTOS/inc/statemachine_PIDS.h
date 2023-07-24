#ifndef __STATEMACHINE_PIDS_H__
#define __STATEMACHINE_PIDS_H__

#include <stdio.h>
#include "FreeRTOS.h"
#include "board.h"
#include "sapi.h"
#include "semphr.h"

#define TIMER_MS_PIDS 		5000	


typedef enum {
	
	STATE_PIDS_INIT,
	STATE_PIDS_STOPPED,
	STATE_PIDS_HEAD_STATION,
	STATE_PIDS_TRAIN_RUNNING,
	STATE_PIDS_TRAIN_ARRIVING,
	STATE_PIDS_STATION_ARRIVED

} eSystemState_PIDS;

typedef enum{
	
	evPids_Init,
	evPids_accelEvent,
	evPids_Timeout

} eSystemEvent_PIDS;

typedef eSystemState_PIDS (*pfEventHandler_PIDS)(void);

typedef struct{

	eSystemState_PIDS 		fsmState;
	eSystemEvent_PIDS 		fsmEvent;
	pfEventHandler_PIDS		fsmHandler;

} sStateMachine_PIDS;

eSystemState_PIDS 	pids_initHandler(void);
eSystemState_PIDS   pids_headStationMessagingHandler(void);
eSystemState_PIDS 	pids_headStationHandler(void);
eSystemState_PIDS 	pids_trainRunningHandler(void);
eSystemState_PIDS 	pids_trainArrivingHandler(void);
eSystemState_PIDS 	pids_stationMessagingHandler(void);

#endif