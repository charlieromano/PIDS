/*****************************************************************************
 * Copyright (c) 2020, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2020/06/25
 * Version: 1.0
 ****************************************************************************/

#include "main.h"


DEBUG_PRINT_ENABLE;

SemaphoreHandle_t    mutexUART; //Mutex que protege la UART de concurrencia
SemaphoreHandle_t    mutexSPI;

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   uint8_t Error_state = 0;

   // res=
   // xTaskCreate( vTaskButton, (const char *)"Tec1", configMINIMAL_STACK_SIZE*2, &Buttons_SM[0], tskIDLE_PRIORITY+1, 0);
   // if(res==pdFAIL) printf("ERROR_TASK_CREATE_BUTTON");

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
