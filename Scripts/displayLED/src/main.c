/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/04/16
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


int main(void)
{

   boardConfig();
   
   debugPrintConfigUart( UART_USB, UART_BAUD_RATE);
   IRQ_GPIO_Init();
   IRQ_UART_Init();

   portInit();
   initDisplayTest();

   /* Create the semaphores, queues, timers and task for ISR_GPIO */

   xMutexUART = xSemaphoreCreateMutex();
   if (xMutexUART == NULL){
      perror("Error creating MUTEX for UART");
      return 1;
   }
/***************************************************************************/
   /* Button tasks */

   if( (timerHandle_button = xTimerCreate( "Timer button", 50, true, NULL, 
      timerCallback_button)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   if(xTimerStart(timerHandle_button, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }


   xBinarySemaphore = xSemaphoreCreateBinary();
   if (xBinarySemaphore == NULL){
      perror("Error creating semaphore");
      return 1;
   }

   if( xTaskCreate( vHandlerTaskGPIO, "ISR GPIO Handler task", 
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

   if( xTaskCreate( vTaskButton, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_button) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

/***************************************************************************/
   /* UART tasks */

   if( (timerHandle_UART = xTimerCreate( "Timer UART ", 800, true, NULL, 
      timerCallback_UART)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   if(xTimerStart(timerHandle_UART, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }

   xBinarySemaphoreUART = xSemaphoreCreateBinary();
   if (xBinarySemaphoreUART == NULL){
      perror("Error creating UART semaphore");
      return 1;
   }

   if( xTaskCreate( vHandlerTaskUART, "ISR UART Handler task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      NULL) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   dataBufferQueue = xQueueCreate(MAX_BUFFER_SIZE, sizeof(uint8_t));
   if (dataBufferQueue == NULL){
      perror("Error creating queue");
      return 1;
   }


   if( xTaskCreate( vTaskUART_buffer, "Receing data task", 
      configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

/***************************************************************************/
   
   /* displayLED tasks */



   if( (timerHandle_displayCLK = xTimerCreate( "Timer display LED", DISPLAY_LED_CLK, true, NULL, 
      timerCallback_displayCLK)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   if(xTimerStart(timerHandle_displayCLK, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }


   if( (timerHandle_displaySTR = xTimerCreate( "Timer display LED", STR_DUTY_CYCLE_PERIOD*portTICK_RATE_MS*100, true, NULL, 
      timerCallback_displaySTR)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   if(xTimerStart(timerHandle_displaySTR, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }

/***************************************************************************/

   /* Start RTOS */
   printf("Init scheduler..\r\n");
   vTaskStartScheduler();   // Scheduler

   while(true);

   return 0;
}

