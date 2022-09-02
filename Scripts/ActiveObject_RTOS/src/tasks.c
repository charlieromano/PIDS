//tasks.c
#include "tasks.h"

/***************************************************************************/
/* State Machine AB tasks */
/***************************************************************************/

void timerCallbackAB(TimerHandle_t xTimerHandle){
/* Timer */

   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB;

   if(cnt%4==0){
   	data_AB  = evTimeout_A;
      if(xQueueSend(queueHandleAB, &data_AB, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }   	
   }
   if(cnt%15==0){   
   	data_AB  = evTimeout_B;
      if(xQueueSend(queueHandleAB, &data_AB, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }
   }
}

void vTaskAB(void *xTimerHandle){
/* Active Object */

	(void)xTimerHandle;
	eSystemEvent_AB newEvent;
	
	while(true){
		if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
			printf("Task AB is running.\r\n");
			xSemaphoreGive(xMutexUART);
		}

      /* fsmAB init */
      eSystemEvent_button newEvent = evInit_AB;
      eSystemState_button nextState = STATE_INIT_AB;
      fsmButton[nextState].fsmEvent = newEvent; 
      nextState = (*fsmButton[nextState].fsmHandler)();

		while(true){
			if( pdPASS == xQueueReceive(queueHandleAB, &newEvent, portMAX_DELAY)){
				fsmMachineAB[nextState].fsmEvent = newEvent;
				nextState = (*fsmMachineAB[nextState].fsmHandler)();
			}
		}
	}
}

   
/***************************************************************************/
/* Button tasks */
/***************************************************************************/

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

void timerCallbackButton(TimerHandle_t xTimerHandle){

	/* Timer */
	eSystemEvent_button newEventFromTimer;

   if(timer_flag==true){
      timer_cnt++;
      newEventFromTimer = evButtonTimeout;
      if(xQueueSend(queueHandleButton, &newEventFromTimer, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }
   }
}

void vTaskButton(void* pvParameters){
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
	      if( pdPASS == xQueueReceive(queueHandleButton, &newEvent, portMAX_DELAY)){
		      fsmButton[nextState].fsmEvent = newEvent; 
		      nextState = (*fsmButton[nextState].fsmHandler)();
	      }
      }
	}
}

/***************************************************************************/

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

