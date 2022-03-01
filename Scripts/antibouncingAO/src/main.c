/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/28
 * Version: 1.0
 ****************************************************************************/

#include "main.h"



void My_IRQ_Init (void);

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );
   My_IRQ_Init();

   /* Create the task */
   if( xTaskCreate( vTaskTA, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_AB) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   /* Create the task */
   if( xTaskCreate( vTaskTB, "State Machine using active object", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      &xTaskStateMachineHandler_button) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   /* Create the task */

   if( xTaskCreate( vHandlerTask, "ISR Handler task", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 
      NULL) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   /* Create the queue*/
   queueHandle_button = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   queueHandle_AB = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_AB));

   /* Create the timer */
   if( (timerHandle_button = xTimerCreate( "Timer1", 500, true, NULL, 
      timerCallback_button)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }
   
   if( (timerHandle_AB = xTimerCreate( "Timer2", 2000, true, NULL, 
      timerCallback_AB)) == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   xBinarySemaphore = xSemaphoreCreateBinary();
   if (xBinarySemaphore == NULL){
      perror("Error creating semaphore");
      return 1;
   }

   /* Start the timer */
   xTimerStart(timerHandle_button, 0);
   xTimerStart(timerHandle_AB, 0);


   /* Start RTOS */
printf("FLAG  OK/NO OK\r\n");
   vTaskStartScheduler();   // Scheduler

   while(true);

   return 0;
}

void timerCallback_button(TimerHandle_t xTimerHandle){

   eSystemEvent_button data_button = evPushed;
   xQueueSend(queueHandle_button, &data_button, 0U);
}

void timerCallback_AB(TimerHandle_t xTimerHandle){
   static uint8_t cnt = 0;
   cnt++;

   eSystemEvent_AB data_AB = cnt%4;
   xQueueSend(queueHandle_AB, &data_AB, 0U);
}


#define MY_ASSERT(CONDICION) my_assert_debug(CONDICION)
//Inicio IRQs
void My_IRQ_Init (void){

      //Inicializamos las interrupciones (LPCopen)
      Chip_PININT_Init(LPC_GPIO_PIN_INT);

      //Inicializamos cada evento de interrupcion (LPCopen)

      // TEC1 FALL
      Chip_SCU_GPIOIntPinSel(0, 0, 4);    //(Canal 0 a 7, Puerto GPIO, Pin GPIO)
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);//Se configura el canal para que se active por flanco
      Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);//Se configura para que el flanco sea el de bajada

      // TEC1 RISE
/*      Chip_SCU_GPIOIntPinSel(1, 0, 4); //(Canal 0 a 7, Puerto GPIO, Pin GPIO)
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1);//Se configura el canal para que se active por flanco
      Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1);//En este caso el flanco es de subida
*/
      //Una vez que se han configurado los eventos para cada canal de interrupcion
      //Se activan las interrupciones para que comiencen a llamar al handler
      NVIC_SetPriority(PIN_INT0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
      NVIC_EnableIRQ(PIN_INT0_IRQn);
/*      NVIC_SetPriority(PIN_INT1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
      NVIC_EnableIRQ(PIN_INT1_IRQn);
*/

}


void GPIO0_IRQHandler(void){

   /* Prevent another ISR or task with higher priority block this ISR*/
   BaseType_t xHigherPriorityTaskWoken = pdFALSE; 

   if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0){ //Verificamos que la interrupciÃ³n es la esperada
      Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupciÃ³n

      gpioWrite(LED2, ON);
      printf("INTERRUPT!:GPIO0_IRQHandler\r\n");
      xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);

   /* YIELD returns a valid value and will request a context switch. 
    * If xHigherPriorityTaskWoken is still pdFALSE 
    * then calling portYIELD_FROM_ISR() will have no effect.
    */
   }
   portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

