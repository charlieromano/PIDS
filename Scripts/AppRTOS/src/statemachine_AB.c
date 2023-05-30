//statemachine_AB.c
#include "statemachine_AB.h"

sStateMachine_AB fsmMachineAB [] = 
{
	{STATE_INIT_AB, evInit_AB, InitHandler_AB},
	{STATE_A, evTimeout_A, AtoBHandler},
	{STATE_B, evTimeout_B, BtoAHandler}
};

eSystemState_AB 	InitHandler_AB(void){ 
	printf("State Machine Init...\n");
	return STATE_A; 
}

eSystemState_AB 	AtoBHandler(void){
	printf("STATE_A;\n");
	return STATE_B; 
}
eSystemState_AB 	BtoAHandler(void){ 
	printf("STATE_B;\n");
	return STATE_A; 
}
