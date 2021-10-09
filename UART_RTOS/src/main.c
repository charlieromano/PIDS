/*****************************************************************************
 * Copyright (c) 2021, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2021/10/08
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


DEBUG_PRINT_ENABLE;

SemaphoreHandle_t    mutexUART; //Mutex que protege la UART de concurrencia
SemaphoreHandle_t    mutexSPI;

uint8_t dato  = 0;

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   uint8_t Error_state = 0;
   BaseType_t res;


   uint8_t dato1 = 1;
   uint8_t dato2 = 78;
   int32_t dato3 = 1234;

   /* Buffer */
   static char uartBuff[10];

   uartWriteByte( UART_USB, 'H' );  // Envia 'H'
   uartWriteByte( UART_USB, 'o' );  // Envia 'o'
   uartWriteByte( UART_USB, 'l' );  // Envia 'l'
   uartWriteByte( UART_USB, 'a' );  // Envia 'a'
   uartWriteByte( UART_USB, '\r' ); // Envia '\r', retorno de carro
   uartWriteByte( UART_USB, '\n' ); // Envia '\n', nueva linea

   char miTexto[] = "Chau\r\n";
   uartWriteString( UART_USB, miTexto );
   
   // Conversion de muestra entera a ascii con base decimal usando itoa()
   itoa( dato3, uartBuff, 10 ); // base 10 significa decimal
   uartWriteString( UART_USB, uartBuff );
   uartWriteString( UART_USB, "\r\n" ); // Enviar un Enter

   perror("Error test");

   if( xTaskCreate( vTaskEchoUART, NULL, configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}
