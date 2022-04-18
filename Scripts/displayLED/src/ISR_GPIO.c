/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/28
 * Version: 1.0
 ****************************************************************************/
#include 	 "ISR_GPIO.h"

#define MY_ASSERT(CONDICION) my_assert_debug(CONDICION)
//Inicio IRQs
void IRQ_GPIO_Init (void){

      //Inicializamos las interrupciones (LPCopen)
      Chip_PININT_Init(LPC_GPIO_PIN_INT);

      //Inicializamos cada evento de interrupcion (LPCopen)

      // TEC1 FALL
      Chip_SCU_GPIOIntPinSel(0, 0, 4);    //(Canal 0 a 7, Puerto GPIO, Pin GPIO)
      Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);//Se configura el canal para que se active por flanco
      Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);//Se configura para que el flanco sea el de bajada

      //Una vez que se han configurado los eventos para cada canal de interrupcion
      //Se activan las interrupciones para que comiencen a llamar al handler
      NVIC_SetPriority(PIN_INT0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
      NVIC_EnableIRQ(PIN_INT0_IRQn);

}


void GPIO0_IRQHandler(void){
   /* GPIO0_IRQHandler must be the name for LPC Interrupt routines for GPIO0*/

   /* Prevent another ISR or task with higher priority block this ISR*/
   BaseType_t xHigherPriorityTaskWoken = pdFALSE; 

   if(Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0){
      Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0);
      gpioWrite(led, ON);
      printf("INTERRUPT!:GPIO0_IRQHandler\r\n");
      xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
   }
   portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

