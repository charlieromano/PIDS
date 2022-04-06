#ifndef STATEMACHINE_PIDS_H
#define STATEMACHINE_PIDS_H

#include "sapi.h"
#include "board.h"
#include <stdio.h>

typedef enum {
	
	STATE_INIT_PIDS,
	STATE_PIDS_HEAD_STATION,
	STATE_PIDS_TRAIN_STOPPED,
	STATE_PIDS_TRAIN_RUNNING,
	STATE_PIDS_TRAIN_ARRIVING,
	STATE_PIDS_STATION_ARRIVED

} eSystemState_PIDS;

typedef enum{

	evPidsInit,
	evPidsHeadStation,
	evPidsEndRoute,
	evPidsTrainStation,
	evPidsTrainRunning,
	evPidsTrainSlowingDown,
	evPidsTrainStopped,

} eSystemEvent_PIDS;

typedef eSystemState_PIDS (*pfEventHandler_PIDS)(void);

typedef struct{
	eSystemState_PIDS 		fsmState;
	eSystemEvent_PIDS 		fsmEvent;
	pfEventHandler_PIDS		fsmHandler;
} sStateMachine_PIDS;

eSystemState_PIDS 	InitHandler_PIDS(void);
eSystemState_PIDS 	trainRunningHandler(void);
eSystemState_PIDS 	trainSlowingDownHandler(void);
eSystemState_PIDS 	trainArrivingHandler(void);
eSystemState_PIDS 	trainStoppedHandler(void);
eSystemState_PIDS 	trainHeadStationHandler(void);
eSystemState_PIDS 	trainEndOfRouteHandler(void);

#endif
