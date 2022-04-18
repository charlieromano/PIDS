//statemachine_PIDS.c
#include "statemachine_PIDS.h"

eSystemState_PIDS 	InitHandler_PIDS(void){ 

	return STATE_PIDS_TRAIN_STOPPED;

}

eSystemState_PIDS 	trainRunningHandler(void){ 

	return STATE_PIDS_TRAIN_RUNNING;

}

eSystemState_PIDS 	trainSlowingDownHandler(void){ 

	return STATE_PIDS_TRAIN_ARRIVING;

}

eSystemState_PIDS 	trainArrivingHandler(void){

	return STATE_PIDS_STATION_ARRIVED;

}

eSystemState_PIDS 	trainStoppedHandler(void){ 

	if(true){
		return STATE_PIDS_STATION_ARRIVED;
	}
	else{
		return STATE_PIDS_HEAD_STATION;
	}
	
}

eSystemState_PIDS 	trainHeadStationHandler(void){ 

	return STATE_PIDS_HEAD_STATION;
}

eSystemState_PIDS 	trainEndOfRouteHandler(void){ 

}

sStateMachine_PIDS fsmPIDS[] = 
{
	{STATE_INIT_PIDS, evPidsInit, InitHandler_PIDS},
	{STATE_PIDS_TRAIN_STOPPED, evPidsTrainRunning, trainRunningHandler},
	{STATE_PIDS_TRAIN_RUNNING, evPidsTrainSlowingDown, trainSlowingDownHandler},
	{STATE_PIDS_TRAIN_ARRIVING, evPidsTrainStopped, trainArrivingHandler},
	{STATE_PIDS_STATION_ARRIVED, evPidsTrainStopped, trainHeadStationHandler},
	{STATE_PIDS_HEAD_STATION, evPidsTrainRunning, trainRunningHandler}

};
