//tasks.c
#include "tasks.h"


void vTaskTA(void *xTimerHandle)
{
	(void)xTimerHandle;
	eSystemEvent_button newEvent;

	while(true){
		vPrintString("Task TA is running.\r\n");
		eSystemState_button nextState = STATE_BUTTON_DOWN;
		newEvent=evPushed;
		int i=0;

		while(true){
			xQueueReceive(queueHandle_button, &data_button, portMAX_DELAY);
			newEvent = data_button;
			fsmButton[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmButton[nextState].fsmHandler)();
			i++;
		}
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler_button);
	}
}


void vTaskTB(void *xTimerHandle)
{
	(void)xTimerHandle;
	eSystemEvent_AB newEvent;

	while(true){
		vPrintString("Task TB is running.\r\n");
		eSystemState_AB nextState = STATE_INIT_AB;
		newEvent=evInit_AB;
		int i=0;

		while(true){
			xQueueReceive(queueHandle_AB, &data_AB, portMAX_DELAY);
			newEvent = data_AB;
			fsmMachineAB[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmMachineAB[nextState].fsmHandler)();
			i++;
		}
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler_AB);
	}
}


void vHandlerTask(void *pvParameters){

   while(true){
      xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
      gpioWrite(LED2, OFF);
      printf("HandlerTask: processing event..\r\n");
   }
}

extern   uint8_t dato;

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
