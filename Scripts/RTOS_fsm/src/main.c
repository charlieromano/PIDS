/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/06
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


DEBUG_PRINT_ENABLE;
uint8_t dato  = 0; //variable global

xTaskHandle xTaskStateMachineHandler;

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   if( xTaskCreate( vTaskStateMachine, "State Machine test", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, &xTaskStateMachineHandler) 
      == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}
