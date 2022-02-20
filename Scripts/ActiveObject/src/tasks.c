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

		while(i<20){
			xQueueReceive(queueHandle, &data, portMAX_DELAY);
			newEvent = data;
			fsmTest[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmTest[nextState].fsmHandler)();
			i++;
		}
	}
}


void vTaskStateMachine(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	eSystemState nextState = STATE_INIT;
	eSystemEvent newEvent;
	int i=0;

	while(true){
		while(i<20){

			if(uartReadByte( UART_USB, &data ))
			{
				if( (data!= '\n') && (data != '\r' ) )
				{
					newEvent=evReceive;
					fsmTest[nextState].fsmEvent == newEvent;
					nextState = (*fsmTest[nextState].fsmHandler)();
					i++;
				}
			}
			else
			{
				//printf("no condition\n;");
				vTaskDelayUntil(&xLastWakeTime, (50/portTICK_RATE_MS));
			}
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
