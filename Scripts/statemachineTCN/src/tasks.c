//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern uint8_t data;
extern sStateMachine fsmTest[];
extern xTaskHandle xTaskStateMachineHandler;

void vTaskStateMachine(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	eSystemState nextState = STATE_INIT;
	eSystemEvent newEvent;
	int i=0;

	while(1){
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
	while(1){
      if(  uartReadByte( UART_USB, &data ) ){
         uartWriteByte( UART_USB, data );
      }		
	}
}
