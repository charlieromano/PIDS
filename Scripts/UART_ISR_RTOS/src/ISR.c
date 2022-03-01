/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/02/28
 * Version: 1.0
 ****************************************************************************/
#include 		 "ISR.h"

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
/*    
      NVIC_SetPriority(PIN_INT1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
      NVIC_EnableIRQ(PIN_INT1_IRQn);
*/

}


void GPIO0_IRQHandler(void){
   /* GPIO0_IRQHandler must be the name for LPC Interrupt routines for GPIO0*/

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

