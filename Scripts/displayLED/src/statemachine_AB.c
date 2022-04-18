//statemachine_AB.c
#include "statemachine_AB.h"

eSystemState_AB 	InitHandler_AB(void){ 
	if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      	printf("State Machine Init...\n");
      	xSemaphoreGive(xMutexUART);
    }
	return STATE_A; 
}

eSystemState_AB 	AtoBHandler(void){
	if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      	printf("STATE_A;\n");
      	xSemaphoreGive(xMutexUART);
    }
	return STATE_B; 
}
eSystemState_AB 	BtoAHandler(void){ 
	if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
		printf("STATE_B;\n");
      	xSemaphoreGive(xMutexUART);
    }
	return STATE_A; 
}

sStateMachine_AB fsmMachineAB [] = 
{
	{STATE_INIT_AB, evInit_AB, InitHandler_AB},
	{STATE_A, evTimeout_A, AtoBHandler},
	{STATE_B, evTimeout_B, BtoAHandler}
};
