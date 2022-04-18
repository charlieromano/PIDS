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

   xMutexUART = xSemaphoreCreateMutex();
   if (xMutexUART == NULL){
      perror("Error creating MUTEX for UART");
      return 1;
   }

   xBinarySemaphoreUART = xSemaphoreCreateBinary();
   if (xBinarySemaphoreUART == NULL){
      perror("Error creating UART semaphore");
      return 1;
   }

/*
   if( xTaskCreate( vTaskTB, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_button) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/
   if( xTaskCreate( vHandlerTaskGPIO, "ISR GPIO Handler task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      NULL) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( xTaskCreate( vHandlerTaskUART, "ISR UART Handler task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      NULL) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }



   queueHandle_button = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   if (queueHandle_button == NULL){
      perror("Error creating queue");
      return 1;
   }
/*
   queueHandle_AB = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   if (queueHandle_AB == NULL){
      perror("Error creating queue");
      return 1;
   }
*/
   queueHandleUART_AO = xQueueCreate(QUEUE_ACTIVE_OBJECT, sizeof(eSystemEvent_UART));
   if (queueHandleUART_AO == NULL ){
      perror("Error creating queue");
      return 1;
   }

   queueCommRx = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(char));
   if (queueCommRx == NULL){
      perror("Error creating queue");
      return 1;
   }

   queueCommTx = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(char));
   if (queueCommTx == NULL){
      perror("Error creating queue");
      return 1;
   }

   if( xTaskCreate( vTaskUART, "UART receiving and dispatch task", 
      configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/
   if( xTaskCreate( vTaskButton, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_button) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
/*
   if( (timerHandle_AB = xTimerCreate( "Timer2", 1000, true, NULL, 
      timerCallback_AB)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }
*/
   if( (timerHandle_button = xTimerCreate( "Timer button", 50, true, NULL, 
      timerCallback_button)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   if(xTimerStart(timerHandle_button, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }
/*
   if(xTimerStart(timerHandle_AB, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }
*/
   /* Start RTOS */
   printf("Init scheduler..\r\n");
   vTaskStartScheduler();   // Scheduler

   while(true);

   return 0;
}

