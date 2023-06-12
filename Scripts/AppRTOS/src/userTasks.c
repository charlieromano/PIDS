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
         perror("Error sending data to the queueHandle_button\r\n");
   }
}

      
void vTaskAB(void *xTimerHandle)
{
   (void)xTimerHandle;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      vPrintString("Task AB is running.\r\n");
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
/* Button taks */
/***************************************************************************/

void timerCallback_button(TimerHandle_t xTimerHandle){

   // Timer 
   eSystemEvent_button newEventFromTimer;

   if(timer_flag==true){
      timer_cnt++;
      newEventFromTimer = evButtonTimeout;
      if(xQueueSend(queueHandle_button, &newEventFromTimer, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }
   }
}

void vHandlerTaskGPIO(void* pvParameters){

   // IRQ Handler task 
   eSystemEvent_button newEventFromISR;
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      vPrintString("Handler ISR GPIO is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   while(true){
      if(pdTRUE ==xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)){
         gpioWrite(led, OFF);
         newEventFromISR = evPushed;
         if(xQueueSend(queueHandle_button, &newEventFromISR, 0U)!=pdPASS){
            perror("Error sending data to the queueHandle_button\r\n");
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
/* State Machine display Led tasks */
/***************************************************************************/


void timerCallback_displayLed(TimerHandle_t xTimerDisplayHandle){
/*
*/

   static uint8_t cnt = 0;
   cnt++;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      //printf("Timer display led is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   eSystemEvent_displayLed  displayLed_timer_event = evDisplayled_timeout;
   
   if(xQueueSend(queueHandle_displayLed, &displayLed_timer_event, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_displayLed\r\n");
   }
}

      
void vTaskDisplayLed(void *xTimerDisplayHandle)
{
   (void)xTimerDisplayHandle;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("Task display led is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }
   

   while(true){

      // fsmDisplayLed init 
      eSystemEvent_displayLed newEvent    = evDisplayled_init;
      eSystemState_displayLed nextState   = STATE_DISPLAYLED_INIT;
      fsmDisplayLed[nextState].fsmEvent   = newEvent; 
      nextState = (*fsmDisplayLed[nextState].fsmHandler)();

      // Active object
      while(true){

        if( pdPASS == xQueueReceive(queueHandle_displayLed, &newEvent, portMAX_DELAY)){
            fsmDisplayLed[nextState].fsmEvent = newEvent; 
            nextState = (*fsmDisplayLed[nextState].fsmHandler)();
         }
      }
   }
      vPrintString("This task is running and about to delete itself.\r\n");
      vTaskDelete(xTaskStateMachineHandler_displayLed);
}
/***************************************************************************/
// Globals
static char *msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;
const uint8_t buf_len = 8;
extern bool_t  displayled_msg_flag;
 uint8_t idx = 0;

void vTaskTest( void *pvParameters ){

   portTickType xPeriodicity =  3000 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("Task Test for messages.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   while(true) {
      
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
      eSystemEvent_displayLed  displayLed_msg_event = evDisplayled_msg_received;
      displayled_msg_flag=1;
/*
      if(xQueueSend(queueHandle_displayLed, &displayLed_msg_event, 0U)!=pdPASS){
         perror("Error sending msg to the queueHandle_displayLed\r\n");
      }
*/

   }
}


/***************************************************************************/
/* UART tasks */
/***************************************************************************/

void timerCallback_UART(TimerHandle_t xTimerHandle){

   // Timer 

   extern uint8_t data_array[];

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      for(int i=0; i<MAX_BUFFER_SIZE; i++){
         printf("%c", data_array[i]);
      }
      printf("\r\n");
      xSemaphoreGive(xMutexUART);
   }

   /*
   eSystemEvent_UART newEventFromTimer;
   if(xQueueSend(queueHandle_UART, &newEventFromTimer, 0U)!=pdPASS){
      perror("Error sending data to the queueHandle_button\r\n");
   }
/*
*/
}

void vHandlerTaskUART(void *pvParameters){

   // IRQ Handler task 
   uint8_t rxData;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      vPrintString("Handler ISR UART is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   // IRQ Handler task 
   eSystemEvent_UART newEventFromISR;

   while(true){

      if(pdTRUE ==xSemaphoreTake(xBinarySemaphoreUART, portMAX_DELAY)){
         gpioWrite(LED3, OFF);

         newEventFromISR = evUart_Received_byte;

         if(xQueueSend(queueHandle_UART, &newEventFromISR, 0U)!=pdPASS){
            perror("Error sending data to the queueHandle_button\r\n");
         }

         IRQ_UART_Init();
      }
   }
}


void vTaskUART(void* xTimerDisplayHandle){

   (void)xTimerDisplayHandle;

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("Task UART is running.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   while(true){

      // fsmUART init 
      eSystemEvent_UART newEvent    = evUart_Init;
      eSystemState_UART nextState   = STATE_UART_INIT;
      fsmUART[nextState].fsmEvent   = newEvent; 
      nextState = (*fsmUART[nextState].fsmHandler)();

      // Active object
      while(true){
         if( pdPASS == xQueueReceive(queueHandle_UART, &newEvent, portMAX_DELAY)){
            gpioWrite(LED3, OFF);
            fsmUART[nextState].fsmEvent = newEvent; 
            nextState = (*fsmUART[nextState].fsmHandler)();
         }
      }
   }
}

/***************************************************************************/





/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

