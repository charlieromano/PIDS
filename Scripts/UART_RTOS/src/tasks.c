//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern   uint8_t dato;
extern   QueueHandle_t xQueue;

void vTaskEchoUART(void* pvParameters){
   // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
	while(1){
      if(  uartReadByte( UART_USB, &dato ) ){
         uartWriteByte( UART_USB, dato );
      }
   }
   vTaskDelete(NULL);
}

void vTaskReadUART(void* pvParameters ){
	while(1){

	}
}

void vTaskWriteUART(void* pvParameters ){

	char	 *pcTaskMessage;
	pcTaskMessage = (char*)pvParameters;
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while(1){
		if(pcTaskMessage!=NULL){
			uartWriteString( UART_USB, (char*)pcTaskMessage );
		}
		vTaskDelayUntil(&xLastWakeTime, (500/portTICK_RATE_MS));
	}
}

void vTaskSender(void* pvParameters ){
	
	BaseType_t 	status;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );

	while(1){
		status = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);
		if(status != pdPASS){
			vPrintString("Couldn't send to the Queue.\r\n");
		}
	}
}

void vTaskReceiver(void* pvParameters ){

	tData 	y;
	BaseType_t status;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 0 );

	while(1){

		if( uxQueueMessagesWaiting(xQueue) != QUEUE_LENGTH ){
			vPrintString("Queue should have been full!\r\n");
		}

		status = xQueueReceive(xQueue, &y, xTicksToWait);

		if(status == pdPASS){
			if(y.id == ID_SRC_01){
				vPrintStringAndNumber("From ID_SRC_01: ", y.data);
			}
			else{
				vPrintStringAndNumber("From ID_SRC_02: ", y.data);
			}
		}
		else{
			vPrintString("Couldn't receive from the Queue.\r\n");
		}
		
	}
}