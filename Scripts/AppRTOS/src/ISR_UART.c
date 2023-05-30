/* UART.c */
#include "ISR_UART.h"


void UART_IRQHandler( void )
{
   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
   
   gpioWrite(LED3, ON);
   printf("UART IRQ!\r\n");
   xSemaphoreGiveFromISR(xBinarySemaphoreUART, &xHigherPriorityTaskWoken);
/*
   uartClearPendingInterrupt(UART_USB);
   uartCallbackClr(UART_USB, UART_RECEIVE);

*/
   portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}

void IRQ_UART_Init( void )
{
   uartConfig(UART_USB, UART_BAUD_RATE);  // Inicializamos la UART

/*
   // Configuramos el callback de recepcion
   uartCallbackSet(UART_USB, UART_RECEIVE, UART_IRQHandler, NULL);
   uartInterrupt(UART_USB, true); // enable interrupt 
*/
}
