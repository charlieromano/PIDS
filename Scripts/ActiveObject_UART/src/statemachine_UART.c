//statemachine_UART.c
#include "statemachine_UART.h"

eSystemState_UART 	InitHandler_UART(void){ 
	printf("UART: State Machine Init...\n");
	return STATE_LISTENING; 
}

eSystemState_UART 	listeningHandler(void){
	printf("evReceive\n");
	return STATE_RECORDING; 
}
eSystemState_UART 	recordingHandler(void){ 
	printf("UART: STATE_;\n");
	return STATE_PROCESSING; 
}

eSystemState_UART 	processingHandler(void){ 
	printf("UART: STATE_;\n");
	return STATE_LISTENING; 
}

sStateMachine_UART fsmUART[] = 
{
	{STATE_INIT_UART, evUartInit, InitHandler_UART},
	{STATE_LISTENING, evUartReceive, listeningHandler},
	{STATE_RECORDING, evUartReceive, recordingHandler},
	{STATE_PROCESSING, evUartEof, processingHandler}
};
