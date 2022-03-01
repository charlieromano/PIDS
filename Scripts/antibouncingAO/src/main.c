/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/28
 * Version: 1.0
 ****************************************************************************/

#include "main.h"

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   /* Create the task */
/*
   if( xTaskCreate( vTaskTA, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, &xTaskStateMachineHandler_AB) 
      == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/
   /* Create the task */
   if( xTaskCreate( vTaskTB, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2, &xTaskStateMachineHandler_button) 
      == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   /* Create the queue*/
   queueHandle_button = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   queueHandle_AB = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_AB));

   /* Create the timer */
/*   if( (timerHandle = xTimerCreate( "Timer1", 5, true, NULL, timerCallback))
      == NULL ) {
      perror("Error creating timer");
      return 1;
   }
   
   if( (timerHandle_B = xTimerCreate( "Timer2", 2000, true, NULL, timerCallback_B))
      == NULL ) {
      perror("Error creating timer");
      return 1;
   }
*/
   /* Start the timer */
/*
   xTimerStart(timerHandle_button, 0);
   xTimerStart(timerHandle_AB, 0);
*/
   /* Start RTOS */
   vTaskStartScheduler();   // Scheduler

   while(true);

   return 0;
}

void timerCallback_button(TimerHandle_t xTimerHandle){
   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_button data = cnt%4;
   xQueueSend(queueHandle_button, &data, 0U);
}

void timerCallback_AB(TimerHandle_t xTimerHandle){
   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB = cnt%4;
   xQueueSend(queueHandle_AB, &data_AB, 0U);
}