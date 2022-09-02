//statemachine_UART.c
#include "statemachine_UART.h"

eSystemState_UART 	InitHandler_UART(void){ 
	printf("UART: State Machine Init...\n");
	return STATE_LISTENING; 
}

eSystemState_UART 	Handler_1(void){
	printf("UART: STATE_;\n");
	return STATE_RECORDING; 
}
eSystemState_UART 	Handler_2(void){ 
	printf("UART: STATE_;\n");
	return STATE_PROCESSING; 
}

sStateMachine_UART fsmMachineUART[] = 
{
	{STATE_INIT_UART, evInit_UART, InitHandler_UART},
	{STATE_LISTENING, evReceive, Handler_1},
	{STATE_RECORDING, evHeader, Handler_2},
	{STATE_PROCESSING, evHeader, Handler_2}
};
