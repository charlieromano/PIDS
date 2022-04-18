//statemachine_LDU.c
#include "statemachine_LDU.h"

eSystemState_LDU 	InitHandler_LDU(void){ 

	return STATE_INIT_LDUx;

}

sStateMachine_LDU fsmLDU[] = 
{
	{STATE_INIT_LDU, evLDUInit, InitHandler_LDU}

};
