/*****************************************************************************
 * Copyright (c) 2022, Carlos German Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/08/28
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

/***************************************************************************/
/* Mutex */
/***************************************************************************/
 
   xMutexUART = xSemaphoreCreateMutex();
   if (xMutexUART == NULL){
      perror("Error creating MUTEX for UART");
      return 1;
   }

/***************************************************************************/
/* GPIO Button task */
/***************************************************************************/

   /* Create the semaphore for interrupt management */   
   xBinarySemaphore = xSemaphoreCreateBinary();
   if (xBinarySemaphore == NULL){
      perror("Error creating semaphore");
      return 1;
   }

   /* Create the interrupt handler task */
   if( xTaskCreate( vHandlerTaskGPIO, "ISR GPIO Handler task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      NULL) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   /* Create the timer */
  if( (timerHandleButton = xTimerCreate( "Timer button", 50, true, NULL, 
      timerCallbackButton)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   /* Start the timer */
   if(xTimerStart(timerHandleButton, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }

   /* Create the queue */
   queueHandleButton = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   if (queueHandle_button == NULL){
      perror("Error creating queue");
      return 1;
   }

   /* Create the task */
   if( xTaskCreate( vTaskButton, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_button) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

/***************************************************************************/
/* State Machine AB tasks */
/***************************************************************************/

   /* Create the timer */
   if( (timerHandleAB = xTimerCreate( "Timer2", 1000, true, NULL, 
      timerCallbackAB)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   /* Start the timer */
   if(xTimerStart(timerHandleAB, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }

   /* Create the queue */
   queueHandleAB = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_AB));
   if (queueHandleAB == NULL){
      perror("Error creating queue");
      return 1;
   }
 
   /* Create the task */
   if( xTaskCreate( vTaskAB, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandlerButton) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
 
/***************************************************************************/
/* UART tasks */
/***************************************************************************/

   /* Create the semaphore for interrupt management */
   xBinarySemaphoreUART = xSemaphoreCreateBinary();
   if (xBinarySemaphoreUART == NULL){
      perror("Error creating UART semaphore");
      return 1;
   }

  /* Option 1: task echo UART */
   if( xTaskCreate( vTaskUART, "Echo test", 
      configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }


/***************************************************************************/
/* Start RTOS */
/***************************************************************************/

   IRQ_GPIO_Init();
   IRQ_UART_Init();

   printf("Init scheduler..\r\n");
   /* Scheduler */
   vTaskStartScheduler();

   while(true);

   return 0;
}

