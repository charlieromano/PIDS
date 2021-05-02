/*==================[inlcusiones]============================================*/

#include "FreeRTOS.h"   //Motor del OS
#include "FreeRTOSConfig.h"
#include "task.h"      //Api de control de tareas y temporizacion
#include "semphr.h"      //Api de sincronizacion (sem y mutex)
#include "queue.h"      //Api de colas
#include "sapi.h"
#include "board.h"

#include "ISR.h"
#include "tasks.h"
#include "types_config.h"


DEBUG_PRINT_ENABLE;

SemaphoreHandle_t    mutexUART; //Mutex que protege la UART de concurrencia
xQueueHandle         q1;
xQueueHandle         q2;
xQueueHandle         q3;

Buttons_SM_t Buttons_SM[1];

int main(void)
{
   uint8_t Error_state = 0;

   boardConfig();
   My_IRQ_Init();

   // UART for debug messages
   debugPrintConfigUart( UART_USB, 115200 );
   printf( "Interrupciones con freeRTOS\r\n" );

   if (NULL == (mutexUART = xSemaphoreCreateMutex())){
         Error_state =1;
   }


   if(xTaskCreate(
      taskLED, (const char *)"Led",
      configMINIMAL_STACK_SIZE*4, 0,
      tskIDLE_PRIORITY+2, 0
      ) == pdFAIL)
   {
      gpioWrite(LEDR,ON);
      printf("ERROR_TASK_LED");
      while(1);
   }


   // Iniciar scheduler
   vTaskStartScheduler();
   
   while( TRUE );

   return 0;
}