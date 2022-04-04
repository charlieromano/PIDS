//tasks.c
#include "tasks.h"

bool timer_flag;
uint8_t timer_cnt;

void vHandlerTaskGPIO(void* pvParameters){

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

void timerCallback_button(TimerHandle_t xTimerHandle){

	eSystemEvent_button newEventFromTimer;

   if(timer_flag==true){
      timer_cnt++;
      newEventFromTimer = evButtonTimeout;
      if(xQueueSend(queueHandle_button, &newEventFromTimer, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }
   }
}

void vTaskButton(void* pvParameters)
{
	
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
			xQueueReceive(queueHandle_button, &newEvent, portMAX_DELAY);
			fsmButton[nextState].fsmEvent = newEvent; 
			nextState = (*fsmButton[nextState].fsmHandler)();
		}
	}
}

void timerCallback_AB(TimerHandle_t xTimerHandle){
   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB = cnt%4;
   xQueueSend(queueHandle_AB, &data_AB, 0U);
}

void vTaskTB(void *xTimerHandle)
{
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
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler_AB);
	}
}


void vHandlerTaskUART(void *pvParameters){

   while(true){
      xSemaphoreTake(xBinarySemaphoreUART, portMAX_DELAY);
      gpioWrite(LED3, OFF);
      if(uartReadByte( UART_USB, &dato ) ){
         if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
         	printf("dato: %c \r\n", dato);
         	xSemaphoreGive(xMutexUART);
         }
      }
      IRQ_UART_Init();
   }
}

void timerCallback_UART(TimerHandle_t xTimerHandle){

/*
	eSystemEvent_UART newEventFromTimer;
   if(xQueueSend(queueHandle_button, &newEventFromTimer, 0U)!=pdPASS){
      perror("Error sending data to the queueHandle_button\r\n");
   }
*/
}

/*
void vTaskUART(void* pvParameters)
{
	
	while(true){

      if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      	printf("vTaskUART is running.\r\n");
      	xSemaphoreGive(xMutexUART);
      }

      eSystemEvent_UART newEvent = evInitUART;
      eSystemState_UART nextState = STATE_UART_INIT;
      fsmButton[nextState].fsmEvent = newEvent; 
		nextState = (*fsmButton[nextState].fsmHandler)();

		while(true){
			xQueueReceive(queueHandle_UART, &newEvent, portMAX_DELAY);
			fsmButton[nextState].fsmEvent = newEvent; 
			nextState = (*fsmButton[nextState].fsmHandler)();
		}
	}
}

*/
void vTaskUART(void* pvParameters){
   
   // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
	while(true){
		if (pdTRUE == xSemaphoreTake(xBinarySemaphoreUART, portMAX_DELAY)){
			gpioWrite(LED3, OFF);
			if(uartReadByte(UART_USB, &rxData)){
			/* dispatch received data and set back ISR */
				if(xQueueSend(queueUART_Rx, &rxData, UART_QUEUE_WAITING_TICKS)!=pdPASS){
				  	/* Data could not be sent after UART_QUEUE_WAITING_TICKS_TIME */
				  	perror("Error sending rxData to the queueUART_Rx");
				}
			}
		}
	}
}
   

