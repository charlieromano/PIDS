/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/28
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, UART_BAUD_RATE);
   IRQ_GPIO_Init();
   IRQ_UART_Init();

   /* Create the semaphores, queues, timers and task for ISR_GPIO */
   xBinarySemaphore = xSemaphoreCreateBinary();
   if (xBinarySemaphore == NULL){
      perror("Error creating semaphore");
      return 1;
   }

   if( xTaskCreate( vHandlerTask, "ISR Handler task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      NULL) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   xBinarySemaphoreUART = xSemaphoreCreateBinary();
   if (xBinarySemaphoreUART == NULL){
      perror("Error creating UART semaphore");
      return 1;
   }

   queueHandle_button = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   if (queueHandle_button == NULL){
      perror("Error creating queue");
      return 1;
   }

   queueHandleUART_AO = xQueueCreate(QUEUE_ACTIVE_OBJECT, sizeof(eSystemEvent_UART));
   if (queueHandleUART_AO == NULL ){
      perror("Error creating queue");
      return 1;
   }

   queueUART_Rx = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(char));
   if (queueUART_Rx == NULL){
      perror("Error creating queue");
      return 1;
   }

   if( xTaskCreate( vTaskUART, "UART receiving and dispatch task", 
      configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( xTaskCreate( vTaskTA, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_button) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( (timerHandle_AB = xTimerCreate( "Timer2", 1000, true, NULL, 
      timerCallback_AB)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }





   if(xTimerStart(timerHandle_AB, 0) != pdPASS){
      /* Start the timer */
      perror("Error starting timer");
      return 1;      
   }

   /* Start RTOS */
   printf("Init scheduler..\r\n");
   vTaskStartScheduler();   // Scheduler

   while(true);

   return 0;
}

void timerCallback_button(TimerHandle_t xTimerHandle){

   eSystemEvent_button data_button = evPushed;
   xQueueSend(queueHandle_button, &data_button, 0U);
}

void timerCallback_AB(TimerHandle_t xTimerHandle){
   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB = cnt%4;
   xQueueSend(queueHandle_AB, &data_AB, 0U);
}


