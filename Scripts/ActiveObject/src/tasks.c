//tasks.c
#include "tasks.h"


void vTaskTA(void *xTimerHandle)
{
	(void)xTimerHandle;
	eSystemEvent newEvent;

	while(true){
		vPrintString("This task is running.\r\n");
		eSystemState nextState = STATE_INIT;
		newEvent=evInit;
		int i=0;

		while(i<10){
			xQueueReceive(queueHandle, &data, portMAX_DELAY);
			newEvent = data;
			fsmTest[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmTest[nextState].fsmHandler)();
			i++;
		}
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler);
	}
}

void vTaskTB(void *xTimerHandle)
{
	(void)xTimerHandle;
	eSystemEvent_B newEvent;

	while(true){
		vPrintString("This task is running.\r\n");
		eSystemState_B nextState = STATE_INIT_B;
		newEvent=evInit_B;
		int i=0;

		while(i<10){
			xQueueReceive(queueHandle_B, &data_B, portMAX_DELAY);
			newEvent = data_B;
			fsmTest_B[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmTest_B[nextState].fsmHandler)();
			i++;
		}
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler);
	}
}


void vTaskEchoUART(void* pvParameters){
   // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
	while(true){
      if(  uartReadByte( UART_USB, &data ) ){
         uartWriteByte( UART_USB, data );
      }		
	}
}
