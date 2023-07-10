/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"

// Task implementation
void myTask( void* taskParmPtr )
{
   // ----- Task setup -----------------------------------
   printf( "Blinky with freeRTOS y sAPI.\r\n" );

   gpioWrite( LED, ON );

   // Send the task to the locked state for 1 s (delay)
   vTaskDelay( 1000 / portTICK_RATE_MS );

   gpioWrite( LED, OFF ); 

   // Periodic task every 500 ms
   portTickType xPeriodicity =  500 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();

   // ----- Task repeat for ever -------------------------
   while(TRUE) {
      gpioToggle( LED );
      printf( "Blink!\r\n" );

      // Send the task to the locked state during xPeriodicity
      // (periodical delay)
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}
/***************************************************************************/
/* State Machine AB tasks */
/***************************************************************************/


void timerCallback_AB(TimerHandle_t xTimerHandle){

   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB = cnt%4;
   if(xQueueSend(queueHandle_AB, &data_AB, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_AB\r\n");
   }
}

      
void vTaskAB(void *xTimerHandle)
{
   (void)xTimerHandle;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("Task AB is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }
   

   while(true){

      // fsmMachineAB init 
      eSystemEvent_AB newEvent = evInit_AB;
      eSystemState_AB nextState = STATE_INIT_AB;
      fsmMachineAB[nextState].fsmEvent = newEvent; 
      nextState = (*fsmMachineAB[nextState].fsmHandler)();

   // Active object
      while(true){

        if( pdPASS == xQueueReceive(queueHandle_AB, &newEvent, portMAX_DELAY)){
            fsmMachineAB[nextState].fsmEvent = newEvent; 
            nextState = (*fsmMachineAB[nextState].fsmHandler)();
         }
      }
      //vPrintString("This task is running and about to delete itself.\r\n");
      //vTaskDelete(xTaskStateMachineHandler);
   }
}

/*
*/
/***************************************************************************/
/* Button tasks */
/***************************************************************************/

void timerCallback_button(TimerHandle_t xTimerHandle){

   // Timer 
   eSystemEvent_button newEventFromTimer;

   if(timer_flag==true){
      timer_cnt++;
      newEventFromTimer = evButtonTimeout;
      if(xQueueSend(queueHandle_button, &newEventFromTimer, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button from timer\r\n");
      }
   }
}

void vHandlerTaskGPIO(void* pvParameters){

   // IRQ Handler task 
   eSystemEvent_button newEventFromISR;
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("Handler ISR GPIO is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   while(true){
      if(pdTRUE ==xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)){
         gpioWrite(LED, OFF);
         newEventFromISR = evPushed;
         if(xQueueSend(queueHandle_button, &newEventFromISR, 0U)!=pdPASS){
            perror("Error sending data to the queueHandle_button from handler\r\n");
         }
      }
   }
}

void vTaskButton(void* pvParameters)
{
/*
*/
   (void)pvParameters;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("vTaskButton is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   while(true){


      // fsmButton init 
      eSystemEvent_button newEvent = evInit;
      eSystemState_button nextState = STATE_BUTTON_INIT;
      fsmButton[nextState].fsmEvent = newEvent; 
      nextState = (*fsmButton[nextState].fsmHandler)();

   // Active Object 
      while(true){
         if( pdPASS == xQueueReceive(queueHandle_button, &newEvent, portMAX_DELAY)){
            fsmButton[nextState].fsmEvent = newEvent; 
            nextState = (*fsmButton[nextState].fsmHandler)();
         }
      }
   }
}

/***************************************************************************/
/* Serial Comm tasks */
/***************************************************************************/

// Settings
static const uint8_t buf_len = 16;

// Globals
static char *msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;

void vTaskReadSerial(void *parameters) {
  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  // Clear whole buffer
  memset(buf, 0, buf_len);
  
  // Loop forever
  while (true) {

    uint8_t c_data=0;
 
    // Read cahracters from serial
    if (uartReadByte( UART_USB, &c_data ) == true ) {
     // dato
     // uartWriteByte( UART_USB, c_data );
     // uartWriteString( UART_USB, "\r\n" );

      // Store received character to buffer if not over buffer limit
      if (idx < buf_len - 1) {
        buf[idx] = c_data;
        idx++;
      }

      // Create a message buffer for print task
      if (c_data == '\n') {

        // The last character in the string is '\n', so we need to replace
        // it with '\0' to make it null-terminated
        buf[idx - 1] = '\0';

        // Try to allocate memory and copy over message. If message buffer is
        // still in use, ignore the entire message.
        if (msg_flag == 0) {
          msg_ptr = (char *)pvPortMalloc(idx * sizeof(char));
          // If malloc returns 0 (out of memory), throw an error and reset
          //configASSERT(msg_ptr);
         if (msg_ptr==NULL){
            if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
               printf("Buffer out of memory\r\n");
               xSemaphoreGive(xMutexUART);
            }
         }

          // Copy message
          memcpy(msg_ptr, buf, idx);

          // Notify other task that message is ready
          msg_flag = 1;
        }

        // Reset receive buffer and index counter
        memset(buf, 0, buf_len);
        idx = 0;
      }
    }
/*
*/
  }
}

void vTaskWriteSerial(void *parameters) {
/*
*/
  while (true) {
    if (msg_flag == 1) {
      uartWriteString(UART_USB, msg_ptr);
      uartWriteString( UART_USB, "\r\n" );

      vPortFree(msg_ptr);
      msg_ptr = NULL;
      msg_flag = 0;
    }
  }
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

