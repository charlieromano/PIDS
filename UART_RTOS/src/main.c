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

   uartWriteByte( UART_USB, 'h' - 32 );   // Envia 'H'
   uartWriteByte( UART_USB, 'A' + 32 );   // Envia 'a'

   /* Enviar un Enter */
   uartWriteByte( UART_USB, '\r' ); // Envia '\r', retorno de carro
   uartWriteByte( UART_USB, '\n' ); // Envia '\n', nueva linea

   uartWriteByte( UART_USB, dato1 + 48 ); // Envia '1'
   uartWriteByte( UART_USB, ' ' );        // Envia ' '
   uartWriteByte( UART_USB, '1' );        // Envia '1'
   uartWriteByte( UART_USB, 32 );         // Envia ' '

   // Convertir un numero entero de 2 di­gitos ASCII y enviar
   uartWriteByte( UART_USB, (dato2/10) + 48 ); // Envia '7'
   uartWriteByte( UART_USB, (dato2%10) + 48 ); // Envia '8'

   uartWriteString( UART_USB, "\r\n" ); // Enviar un Enter

   uartWriteByte( UART_USB, 'H' );  // Envia 'H'
   uartWriteByte( UART_USB, 'o' );  // Envia 'o'
   uartWriteByte( UART_USB, 'l' );  // Envia 'l'
   uartWriteByte( UART_USB, 'a' );  // Envia 'a'
   uartWriteByte( UART_USB, '\r' ); // Envia '\r', retorno de carro
   uartWriteByte( UART_USB, '\n' ); // Envia '\n', nueva linea

   uartWriteString( UART_USB, "Chau\r\n" ); // Envi­a "Chau\r\n"

   char miTexto[] = "Hola de nuevo\r\n";

   uartWriteString( UART_USB, miTexto ); // Envi­a "Hola de nuevo\r\n"

   miTexto[0] = 'h';
   uartWriteString( UART_USB, miTexto ); // Envia "hola de nuevo\r\n"

   // Conversion de muestra entera a ascii con base decimal usando itoa()
   itoa( dato3, uartBuff, 10 ); // base 10 significa decimal
   uartWriteString( UART_USB, uartBuff );

   uartWriteString( UART_USB, "\r\n" ); // Enviar un Enter


   res=
   xTaskCreate( vTaskUART, (const char *)"UART", configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 0);
   if(res==pdFAIL) printf("ERROR_TASK_CREATE_BUTTON");

   // res=
   // xTaskCreate( vTaskReadADC, (const char *)"TaskReadADC()", configMINIMAL_STACK_SIZE*4, &xTaskParamsADC[0], tskIDLE_PRIORITY+1,0  );
   // if(res==pdFAIL) printf("ERROR_TASK_CREATE_ADC");

   // res=
   // xTaskCreate( vTaskProcessing, (const char *)"TaskProcessing()", configMINIMAL_STACK_SIZE*4, &xTaskParamsDataProc[0], tskIDLE_PRIORITY+1,0  );
   // if(res==pdFAIL) printf("ERROR_TASK_CREATE_DATAPROC");

   // res=
   // xTaskCreate( vTaskWriteSPI, (const char *)"TaskWriteSPI()", configMINIMAL_STACK_SIZE*4, &xTaskParamsDataProc[0], tskIDLE_PRIORITY+1,0  );
   // if(res==pdFAIL) printf("ERROR_TASK_CREATE_DATAPROC");

   // Iniciar scheduler
   if (0 == Error_state){

  	  vTaskStartScheduler();   // Scheduler

   } else{
	  printf("Error system init.");
   }

   while(1);

   return 0;
}
