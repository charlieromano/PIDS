//statemachine_IDU.c
#include "statemachine_IDU.h"

eSystemState_IDU 	InitHandler_IDU(void){ 

	return STATE_INIT_IDU;

}

sStateMachine_IDU fsmIDU[] = 
{
	{STATE_INIT_IDU, evIDUInit, InitHandler_IDU}

};
