//tasks.c
#include "tasks.h"

extern uint8_t data;
extern sStateMachine 	fsmTest[]; /* State Machine struct */
extern xTaskHandle 	 	xTaskStateMachineHandler; /* RTOS task handler */
extern TimerHandle_t  	timerHandle; /* RTOS timer */
extern QueueHandle_t 	queueHandle; /* RTOS queue */

static void vTaskTA(void *pvParameters)
{
	(void)xTimerHandle;
	eSystemEvent newEvent;

	while(true){
		vPrintString("This task is running.\r\n");
		eSystemState nextState = STATE_INIT;
		newEvent=evReceive;
		int i=0;

		while(i<10){
			xQueueReceive(queueHandle, &data, portMAX_DELAY);
			fsmTest[nextState].fsmEvent == newEvent; //data.event
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
