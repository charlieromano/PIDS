/* UART.c */
#include "ISR_UART.h"

void IRQ_UART_Init( void )
{
   /* Inicializar la UART_USB */
   uartConfig(UART_USB, UART_BAUD_RATE);  // Inicializamos la UART
   // Configuramos el callback de recepcion
   uartCallbackSet(UART_USB, UART_RECEIVE, UART_ISR_Handler, NULL);
   // Habilito todas las interrupciones de UART_USB
   uartInterrupt(UART_USB, true); // enable interrupt 
/*
*/
}

void UART_ISR_Handler( void *noparam)
{
   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
   
   eSystemEvent_UART newEventFromISR = evUart_Received_byte;

   gpioWrite(LED3, ON);
   //printf("UART IRQ!\r\n");
   if(xQueueSendFromISR(queueHandle_UART, &newEventFromISR, 0U)!=pdPASS){
      perror("Error sending data to the queueHandle_UART from ISR\r\n");
   }
   uartClearPendingInterrupt(UART_USB);
   uartCallbackClr(UART_USB, UART_RECEIVE);
   
   portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
/*
*/
}
