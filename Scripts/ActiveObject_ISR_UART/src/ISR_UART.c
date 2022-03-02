/* UART.c */
#include "ISR_UART.h"
#include "sapi_uart.h"

void IRQ_UART_Init( void )
{
	uartConfig(UART_USB, 115200);	// Inicializamos la UART

	// Configuramos el callback de recepcion
	uartCallbackSet(UART_USB, UART_RECEIVE, UART_IRQHandler, NULL);

	uartInterrupt(UART_USB, true); /* enable interrupt */
}


void UART_IRQHandler( void )
{
   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
   
   gpioWrite(LED3, ON);
   printf("UART INTERRUPT!: UART_IRQHandler\r\n");
   xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
   uartClearPendingInterrupt(UART_USB);
   uartCallbackClr(UART_USB, UART_RECEIVE);

   portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}

//-------------------------------------------------------------
// Interrupts
//-------------------------------------------------------------
/*
// UART Global Interrupt Enable/Disable
void uartInterrupt( uartMap_t uart, bool_t enable );

// UART Interrupt event Enable and set a callback
void uartCallbackSet( uartMap_t uart, uartEvents_t event, 
                      callBackFuncPtr_t callbackFunc, void* callbackParam );
                 
// UART Interrupt event Disable
void uartCallbackClr( uartMap_t uart, uartEvents_t event );

// UART Set Pending Interrupt. Useful to force first character in tx transmission
void uartSetPendingInterrupt(uartMap_t uart);

// UART Clear Pending Interrupt.
void uartClearPendingInterrupt(uartMap_t uart);

typedef enum{
   UART_RECEIVE,
   UART_TRANSMITER_FREE
} uartEvents_t;


*/