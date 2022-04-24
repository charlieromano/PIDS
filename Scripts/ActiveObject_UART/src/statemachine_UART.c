//statemachine_UART.c
#include "statemachine_UART.h"

eSystemState_UART 	InitHandler_UART(void){ 
	printf("UART: State Machine Init...\n");
	return STATE_LISTENING; 
}

eSystemState_UART 	listeningHandler(void){

	/* while listening check if valid 
	 * if valid then record and process
	 * otherwise discard
	 */
/*
    while(uartReadByte( UART_USB, &dato )){
    	if(xQueueSend(dataBuffer, &dato, 0U)!=pdPASS){
    		perror("Error sending data to the dataBuffer\r\n");
    	}
    return STATE_RECORDING; 
    return STATE_LISTENING;
    }
*/
}

eSystemState_UART 	recordingHandler(void){ 
/*
    while(uartReadByte( UART_USB, &dato )){
         uartWriteByte( UART_USB, dato );
    }
    return STATE_PROCESSING; 
*/
}

eSystemState_UART 	processingHandler(void){ 
	printf("UART: STATE_;\n");
	return STATE_LISTENING; 
}

sStateMachine_UART fsmUART[] = 
{
	{STATE_UART_INIT, evUartInit, InitHandler_UART},
	{STATE_LISTENING, evUartReceive, listeningHandler},
	{STATE_RECORDING, evUartReceive, recordingHandler},
	{STATE_PROCESSING, evUartEof, processingHandler}
};
