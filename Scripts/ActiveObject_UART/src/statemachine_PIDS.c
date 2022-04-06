//statemachine_PIDS.c
#include "statemachine_PIDS.h"

eSystemState_PIDS 	InitHandler_PIDS(void){ 

}

eSystemState_PIDS 	trainRunningHandler(void){ 

}

eSystemState_PIDS 	trainSlowingDownHandler(void){ 

}

eSystemState_PIDS 	trainArrivingHandler(void){

}

eSystemState_PIDS 	trainStoppedHandler(void){ 

}

eSystemState_PIDS 	trainHeadStationHandler(void){ 

}

eSystemState_PIDS 	trainEndOfRouteHandler(void){ 

}

sStateMachine_PIDS fsmPIDS[] = 
{
	{STATE_INIT_PIDS, evPidsInit, InitHandler_PIDS},
};
