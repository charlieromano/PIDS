/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "main.h"

int main( void )
{
   boardInit();
   boardConfig();
   //debugPrintConfigUart( UART_USB, UART_BAUD_RATE);

   IRQ_GPIO_Init();
   IRQ_UART_Init();

   portInit();
   displayInit();

/*

   // Create a task in freeRTOS with dynamic memory
   xTaskCreate(
      myTask,                     // Function that implements the task.
      (const char *)"myTask",     // Text name for the task.
      configMINIMAL_STACK_SIZE*2, // Stack size in words, not bytes.
      0,                          // Parameter passed into the task.
      tskIDLE_PRIORITY+1,         // Priority at which the task is created.
      0                           // Pointer to the task created in the system
   );
*/

   xMutexUART = xSemaphoreCreateMutex();
   if (xMutexUART == NULL){
      perror("Error creating MUTEX for UART");
      return 1;
   }
   
/***************************************************************************/
/* State Machine AB */
/***************************************************************************/
/*
   // Create the timer
   if( (timerHandle_AB = xTimerCreate( "Timer2", 2000/4, true, NULL, timerCallback_AB))
      == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   // Start the timer
   if(xTimerStart(timerHandle_AB, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }

   // Create the queue
   queueHandle_AB = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_AB));
   if (queueHandle_AB == NULL){
      perror("Error creating queue");
      return 1;
   }

   // Create the task 
   if( xTaskCreate( vTaskAB, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2, &xTaskStateMachineHandler_AB) 
      == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/
/***************************************************************************/
/* Button */
/***************************************************************************/
/*
*/
   if( (timerHandle_button = xTimerCreate( "Timer button", 
      10, true, NULL, 
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

   queueHandle_button = xQueueCreate(QUEUE_MAX_LENGTH, 
      sizeof(eSystemEvent_button));
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
/* display Led */
/***************************************************************************/

/*
   if( (timerHandle_displayLed = xTimerCreate( "Timer displayLed", 
      DISPLAYLED_TIMEOUT_MS, true, NULL, 
      timerCallback_displayLed)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   if(xTimerStart(timerHandle_displayLed, 0) != pdPASS){
      perror("Error starting timer");
      return 1;      
   }

   queueHandle_displayLed = xQueueCreate(QUEUE_MAX_LENGTH, 
      sizeof(eSystemEvent_displayLed));
   if (queueHandle_displayLed == NULL){
      perror("Error creating queue");
      return 1;
   }

   if( xTaskCreate( vTaskDisplayLedTest, "Display Led task", 
      configMINIMAL_STACK_SIZE*4, NULL, tskIDLE_PRIORITY+1, 
      &xTaskDisplayLedTestHandler) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( xTaskCreate( vTaskDisplayLed, "Display Led State Machine task", 
      configMINIMAL_STACK_SIZE*4, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_displayLed) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( xTaskCreate( vTaskTest, "Display Led Testing COMM task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskTestHandler) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/

/***************************************************************************/
/* UART tasks */
/***************************************************************************/

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
/*
   queueHandle_UART = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_UART));
   if (queueHandle_UART == NULL){
      perror("Error creating queue");
      return 1;
   }

   if( xTaskCreate( vTaskUART, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_UART) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
*/

/***************************************************************************/
/* RTOS start */
/***************************************************************************/

   vTaskStartScheduler(); // Initialize scheduler

   while( true ); // If reach heare it means that the scheduler could not start

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
