//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern   uint8_t dato;
extern   QueueHandle_t xQueue;

void vTaskReadUART(void* taskParamPtr ){
	while(1){

	}
}

void vTaskWriteUART(void* taskParamPtr ){
	while(1){
		
	}
}

void vTaskEchoUART(void* taskParamPtr){
    // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   	// Se reenvia el dato a la UART_USB realizando un eco de lo que llega
	while(1){
      if(  uartReadByte( UART_USB, &dato ) ){
         uartWriteByte( UART_USB, dato );
      }		
	}
}

void vTaskSender(void* taskParamPtr ){
	
	int32_t		x;
	BaseType_t 	status;

	x = (int32_t) taskParamPtr;

	while(1){
		status = xQueueSendToBack(xQueue, &x, 0);
		if(status != pdPASS){
			vPrintString("Couldn't send to the Queue.\r\n");
		}
	}
}

void vTaskReceiver(void* taskParamPtr ){

	int32_t 	y;
	BaseType_t status;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );

	while(1){

		if(uxQueueMessagesWaiting(xQueue)!=0){
			vPrintString("Queue should have been empty!\r\n");
		}

		status = xQueueReceive(xQueue, &y, xTicksToWait);

		if(status == pdPASS){
			vPrintStringAndNumber("Received = ", y);
		}
		else{
			vPrintString("Couldn't receive from the Queue.\r\n");
		}
		
	}
}