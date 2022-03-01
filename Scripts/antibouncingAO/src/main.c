/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/28
 * Version: 1.0
 ****************************************************************************/

#include "main.h"

gpioMap_t button=TEC1;
DEBUG_PRINT_ENABLE;

void My_IRQ_Init (void);

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );
//   My_IRQ_Init();

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

   /* Create the queue*/
   queueHandle_button = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_button));
   queueHandle_AB = xQueueCreate(QUEUE_MAX_LENGTH, sizeof(eSystemEvent_AB));

   /* Create the timer */
   if( (timerHandle_button = xTimerCreate( "Timer1", 1000, true, NULL, timerCallback_button))
      == NULL ) {
      perror("Error creating timer");
      return 1;
   }
   
   if( (timerHandle_AB = xTimerCreate( "Timer2", 10000, true, NULL, timerCallback_AB))
      == NULL ) {
      perror("Error creating timer");
      return 1;
   }

   /* Start the timer */
   xTimerStart(timerHandle_button, 0);
   xTimerStart(timerHandle_AB, 0);

   /* Start RTOS */
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

      //Inicializamos de cada evento de interrupcion (LPCopen)

/*      
      GLOBAL! extern pinInitGpioLpc4337_t gpioPinsInit[];
      Chip_SCU_GPIOIntPinSel( j,  gpioPinsInit[i].gpio.port, gpioPinsInit[i].gpio.pin );   // TECi
      Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH( j ) );                      // INTj (canal j -> hanlder GPIOj)       //Borra el pending de la IRQ
      Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH( j ) );                      // INTj //Selecciona activo por flanco
      Chip_PININT_EnableIntLow( LPC_GPIO_PIN_INT, PININTCH( j ) );                        // INTj //Selecciona activo por flanco descendente
      Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH( j ) );                       // INTj //Selecciona activo por flanco ascendente
*/
      // TEC1 FALL
      Chip_SCU_GPIOIntPinSel(0, 0, 4);    //(Canal 0 a 7, Puerto GPIO, Pin GPIO)
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);//Se configura el canal para que se active por flanco
      Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);//Se configura para que el flanco sea el de bajada

      // TEC1 RISE
      Chip_SCU_GPIOIntPinSel(1, 0, 4); //(Canal 0 a 7, Puerto GPIO, Pin GPIO)
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1);//Se configura el canal para que se active por flanco
      Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1);//En este caso el flanco es de subida

      //Una vez que se han configurado los eventos para cada canal de interrupcion
      //Se activan las interrupciones para que comiencen a llamar al handler
      NVIC_SetPriority(PIN_INT0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
      NVIC_EnableIRQ(PIN_INT0_IRQn);
      NVIC_SetPriority(PIN_INT1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
      NVIC_EnableIRQ(PIN_INT1_IRQn);


}
