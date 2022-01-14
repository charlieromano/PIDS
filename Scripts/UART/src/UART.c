/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * ...
 *
 */

#include "sapi.h"         /* <= sAPI header */

/* Callbacks - Declaraciones */

void uartUsbReceiveCallback( void *unused );
void uartUsbSendCallback( void *unused );

void uart232ReceiveCallback( void *unused );
void uart232SendCallback( void *unused );

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar la UART_USB junto con las interrupciones de Tx y Rx */
   uartConfig(UART_USB, 115200);   
   // Seteo un callback al evento de recepcion y habilito su interrupcion
   uartCallbackSet(UART_USB, UART_RECEIVE, uartUsbReceiveCallback, NULL);
   // Seteo un callback al evento de transmisor libre y habilito su interrupcion
   uartCallbackSet(UART_USB, UART_TRANSMITER_FREE, uartUsbSendCallback, NULL);
   // Habilito todas las interrupciones de UART_USB
   uartInterrupt(UART_USB, true);
   
   /* Inicializar la UART_232 */
   uartConfig(UART_232, 115200);
   // Seteo un callback al evento de recepcion y habilito su interrupcion
   uartCallbackSet(UART_232, UART_RECEIVE, uart232ReceiveCallback, NULL);
   // Seteo un callback al evento de transmisor libre y habilito su interrupcion
   uartCallbackSet(UART_232, UART_TRANSMITER_FREE, uart232SendCallback, NULL);   
   // Habilito todas las interrupciones de UART_232
   uartInterrupt(UART_232, true);

   // Envío para identificar cual es cual y para arrancar la secuencia (si no
   // hasta que no se envie un byte desde cada terminal no funciona)
   uartWriteByte(UART_USB, 'u');
   uartWriteByte(UART_USB, 's');
   uartWriteByte(UART_USB, 'b');
   uartWriteByte(UART_232, '2');

   /* ------------- REPETIR POR SIEMPRE ------------- */

   while(1) {
      /* Sleep until next Interrupt happens */
      sleepUntilNextInterrupt();
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/* Callbacks - Implementaciones */


uint8_t dataToSendToUart232 = 0;
bool_t dataToSendToUart232Pending = FALSE;

// Recibo de la PC en la UART_USB
void uartUsbReceiveCallback( void *unused )
{
   dataToSendToUart232 = uartRxRead(UART_USB);
   gpioWrite(LEDR,ON);
   dataToSendToUart232Pending = TRUE;
}

// Envio a la PC desde la UART_232
void uart232SendCallback( void *unused )
{
   if(dataToSendToUart232Pending){
      uartTxWrite(UART_232, dataToSendToUart232);
      dataToSendToUart232 = 0;
      gpioWrite(LEDG,ON);
      dataToSendToUart232Pending = FALSE;
   }
}

uint8_t dataToSendToUartUsb = 0;
bool_t dataToSendToUartUsbPending = FALSE;

// Recibo de la PC en la UART_232
void uart232ReceiveCallback( void *unused )
{
   dataToSendToUartUsb = uartRxRead(UART_232);
   dataToSendToUartUsbPending = TRUE;
   gpioWrite(LEDB,ON);
}

// Envio a la PC desde la UART_USB
void uartUsbSendCallback( void *unused )
{
   if(dataToSendToUartUsbPending){
      uartTxWrite(UART_USB, dataToSendToUartUsb);
      dataToSendToUartUsb = 0;
      dataToSendToUartUsbPending = FALSE;
      gpioWrite(LEDB,OFF);
   }
}
