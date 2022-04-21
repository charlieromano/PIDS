//tasks.c
#include "tasks.h"

bool timer_flag;
uint8_t timer_cnt;

/***************************************************************************/
/* State Machine AB tasks */
/***************************************************************************/

void timerCallback_AB(TimerHandle_t xTimerHandle){

	/* Timer */

   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB = cnt%4;
   xQueueSend(queueHandle_AB, &data_AB, 0U);
}

void vTaskTB(void *xTimerHandle)
{

	/* Active Object */

	(void)xTimerHandle;
	eSystemEvent_AB newEvent;

	while(true){
      if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      	printf("Task TB is running.\r\n");
      	xSemaphoreGive(xMutexUART);
      }
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
		vTaskDelete(xTaskStateMachineHandler_AB);
	}
}

   
/***************************************************************************/
/* Button tasks */
/***************************************************************************/

void timerCallback_button(TimerHandle_t xTimerHandle){

	/* Timer */

	eSystemEvent_button newEventFromTimer;

   if(timer_flag==true){
      timer_cnt++;
      newEventFromTimer = evButtonTimeout;
      if(xQueueSend(queueHandle_button, &newEventFromTimer, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }
   }
}

void vHandlerTaskGPIO(void* pvParameters){

	/* IRQ Handler task */

	eSystemEvent_button newEventFromISR;

   while(true){

      if(pdTRUE ==xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)){
      	gpioWrite(LED2, OFF);
	      newEventFromISR = evPushed;
	      if(xQueueSend(queueHandle_button, &newEventFromISR, 0U)!=pdPASS){
	      	perror("Error sending data to the queueHandle_button\r\n");
	      }
	   }
	}
}

void vTaskButton(void* pvParameters)
{
	/* Active Object */
	
	while(true){

      if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      	printf("vTaskButton is running.\r\n");
      	xSemaphoreGive(xMutexUART);
      }

      /* fsmButton init */
      eSystemEvent_button newEvent = evInit;
      eSystemState_button nextState = STATE_BUTTON_INIT;
      fsmButton[nextState].fsmEvent = newEvent; 
		nextState = (*fsmButton[nextState].fsmHandler)();

		while(true){
			if( pdPASS == xQueueReceive(queueHandle_button, &newEvent, portMAX_DELAY)){
				fsmButton[nextState].fsmEvent = newEvent; 
				nextState = (*fsmButton[nextState].fsmHandler)();
			}
		}
	}
}

/***************************************************************************/
/* UART tasks */
/***************************************************************************/

void timerCallback_UART(TimerHandle_t xTimerHandle){

	/* Timer */

	eSystemEvent_UART newEventFromTimer;
   if(xQueueSend(queueHandle_UART, &newEventFromTimer, 0U)!=pdPASS){
      perror("Error sending data to the queueHandle_button\r\n");
   }
}

void vHandlerTaskUART(void *pvParameters){

	/* IRQ Handler task */

   while(true){
      xSemaphoreTake(xBinarySemaphoreUART, portMAX_DELAY);
      gpioWrite(LED3, OFF);
      if(uartReadByte( UART_USB, &dato ) ){
      	if(xQueueSend(queueCommRx, &dato, 0U)!=pdPASS){
      		perror("Error sending data to QUEUE_COMM_RX\r\n");
      	}
      }
      IRQ_UART_Init();
   }

}

void vTaskUART(void* pvParameters){
   
   // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   // Se reenvia el dato a la UART_USB realizando un eco de lo que llega

	while(true){
		xSemaphoreTake(xBinarySemaphoreUART, portMAX_DELAY);
      gpioWrite(LED3, OFF);
      printf("HandlerTaskUART: processing event..\r\n");

      
      if(  uartReadByte( UART_USB, &dato ) ){
         uartWriteByte( UART_USB, dato );
         IRQ_UART_Init();
      }
   }
   vTaskDelete(NULL);
}


/***************************************************************************/
