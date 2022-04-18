//tasks.c
#include "tasks.h"

bool timer_flag;
uint8_t timer_cnt;


void vHandlerTaskUART(void *pvParameters){

   while(true){
      xSemaphoreTake(xBinarySemaphoreUART, portMAX_DELAY);
      gpioWrite(LEDG, OFF);
      if(uartReadByte( UART_USB, &dato ) ){
      	if(xQueueSend(queueCommRx, &dato, 0U)!=pdPASS){
      		perror("Error sending data to QUEUE_COMM_RX\r\n");
      	}
      }
      IRQ_UART_Init();
   }
}


void timerCallback_UART(TimerHandle_t xTimerHandle){

	eSystemEvent_UART newEventFromTimer;
   if(xQueueSend(queueHandle_UART, &newEventFromTimer, 0U)!=pdPASS){
      perror("Error sending data to the queueHandle_button\r\n");
   }
}


void vTaskUART(void* pvParameters){
   
}
   


void vHandlerTaskGPIO(void* pvParameters){

	eSystemEvent_button newEventFromISR;

   while(true){

      if(pdTRUE ==xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)){
      	gpioWrite(led, OFF);
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
			if( pdPASS == xQueueReceive(queueHandle_button, &newEvent, portMAX_DELAY)){
				fsmButton[nextState].fsmEvent = newEvent; 
				nextState = (*fsmButton[nextState].fsmHandler)();
			}
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
		vTaskDelete(xTaskStateMachineHandler_AB);
	}
}


