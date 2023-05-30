//statemachine_UART.c
#include "statemachine_UART.h"

extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

sStateMachine_UART fsmUART[] = 
{
	{STATE_UART_INIT, evUartInit, InitHandler_UART},
	{STATE_UART_IDLE, evUartNewFrame, listeningHandler}
/*
	{STATE_UART_LISTENING, evUartNewFrame, listeningHandler},
	{STATE_UART_RECORDING, evUartNewFrame, recordingHandler},
	{STATE_UART_PROCESSING, evUartTimeout, processingHandler}
*/
};


eSystemState_UART 	InitHandler_UART(void){ 
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }
	//printf("UART: State Machine Init...\n");
	//initFrame=-1;
	//endFrame=-1;
	return STATE_UART_IDLE; 
}

eSystemState_UART 	listeningHandler(void){
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_IDLE\r\n");
        xSemaphoreGive(xMutexUART);
    }
	/* while listening check if valid 
	 * if valid then record and process
	 * otherwise keep listening
	 */
/*
	// Buffer scanning 
	if((initFrame==-1) || (endFrame==-1)){
		for(int i=0; i<DATA_ARRAY_LENGTH; i++){
			if(data_array_copy[i] & MASK_HEADER)
				initFrame=i;
			if(data_array_copy[i] & MASK_TRAILER)
				endFrame=i;
		}
	}

	// State's changing 	

	// case init but no end 
	if( (initFrame!=-1) && (endFrame==-1)){
		memcpy(&output_array_copy,&data_array_copy[initFrame], 
			MAX_BUFFER_SIZE - initFrame); 
		return STATE_UART_LISTENING;
	}

	// case init and end 
	if( (initFrame!=-1) && (endFrame!=-1)){
		memcpy(&output_array_copy,&data_array_copy[initFrame], 
			MAX_BUFFER_SIZE - initFrame - endFrame); 
		return STATE_UART_PROCESSING;
	}

	// case no init neither end 
	if( (initFrame==-1) && (endFrame==-1)){
		memcpy(&output_array_copy[MAX_BUFFER_SIZE - initFrame],&data_array_copy, 
			MAX_BUFFER_SIZE - endFrame); 
		return STATE_UART_PROCESSING;
	}
	else
*/
		return STATE_UART_IDLE;
}

eSystemState_UART 	recordingHandler(void){ 
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }


	return STATE_UART_PROCESSING;

}


eSystemState_UART 	processingHandler(void){ 
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }
	return STATE_UART_IDLE;

}
