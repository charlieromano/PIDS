//statemachine_B.c
#include "statemachine_B.h"

eSystemState_B 	InitHandler_B(void){ 
	printf("State Machine Init...\n");
	printf("data:%d \n",data);
	return STATE_A; 
}

eSystemState_B 	AtoBHandler(void){
	printf("STATE_A;\n");
	return STATE_B; 
}
eSystemState_B 	BtoAHandler(void){ 
	printf("STATE_B;\n");
	return STATE_A; 
}

sStateMachine_B fsmTest_B [] = 
{
	{STATE_INIT_B, evInit_B, InitHandler_B},
	{STATE_A, evTimeout1, AtoBHandler},
	{STATE_B, evTimeout2, BtoAHandler}
};
