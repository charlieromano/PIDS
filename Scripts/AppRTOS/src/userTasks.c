/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"
 
/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

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




/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

