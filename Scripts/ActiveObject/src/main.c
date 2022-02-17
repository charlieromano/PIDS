/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/06
 * Version: 1.0
 ****************************************************************************/

#include "main.h"

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   /* Create the task */
   if( xTaskCreate( vTaskStateMachine, "State Machine test", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, &xTaskStateMachineHandler) 
      == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   /* Create the queue*/
   queueHandle = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent));

   /* Create the timer */
   if( (timerHandle = xTimerCreate( "Timer1", 1000, true, NULL, timerCallback))
      == NULL ) {
      perror("Error creating timer");
      return 1;
   }
   
   /* Start the timer */
   xTimerStart(timerHandle, 0);

   /* Start RTOS */
   vTaskStartScheduler();   // Scheduler

   while(true);

   return 0;
}
