/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2021/10/08
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


DEBUG_PRINT_ENABLE;

SemaphoreHandle_t    mutexUART; //Mutex que protege la UART de concurrencia
SemaphoreHandle_t    mutexSPI;

uint8_t dato  = 0;
QueueHandle_t xQueue;

static const char *pcMsgTask1 = "Task1 msg\n";
static const char *pcMsgTask2 = "Task2 msg\n";

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

 /*  if( xTaskCreate( vTaskEchoUART, "Echo test", 
      configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/
   if( xTaskCreate( vTaskWriteUART, "write UART", 
      configMINIMAL_STACK_SIZE, (void*)pcMsgTask1, 
      tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( xTaskCreate( vTaskWriteUART, "write UART2", 
      configMINIMAL_STACK_SIZE, (void*)pcMsgTask2, 
      tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }


   /*
   if( xTaskCreate( vTaskSender, "SENDER 1", 
      configMINIMAL_STACK_SIZE, (tData*)&(xDataFrame[0]), 
      tskIDLE_PRIORITY+2, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
   
   if( xTaskCreate( vTaskSender, "SENDER 2", 
      configMINIMAL_STACK_SIZE, (tData*)&(xDataFrame[1]), 
      tskIDLE_PRIORITY+2, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
   
   if( xTaskCreate( vTaskReceiver, "RECEIVER", 
      configMINIMAL_STACK_SIZE*2, NULL, 
      tskIDLE_PRIORITY+2, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
   */

   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}
