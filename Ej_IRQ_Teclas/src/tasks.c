//tasks.c
#include "FreeRTOS.h"   //Motor del OS
#include "FreeRTOSConfig.h"
#include "task.h"		//Api de control de tareas y temporizaciÃ³n
#include "semphr.h"		//Api de sincronizaciÃ³n (sem y mutex)
#include "queue.h"      //Api de colas
#include "sapi.h"
#include "board.h"

#include "tasks.h"
#include "types_config.h"


#define ANTIREBOTE_MS 20
#define CANT_LEDS 4

extern SemaphoreHandle_t mutexUART;
extern xQueueHandle q1;
extern xQueueHandle q2;
extern xQueueHandle q3;


// Implementacion de funcion de la tarea Led
void taskLED( void* taskParmPtr ){

   printf( "Ejercicio RTOS 1.2\r\n" );
   
   uint8_t i=0;
      
   portTickType xPeriodicity = 1000 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();

   while(1){
      i++;
      printf("Ciclo: %d \r\n", i);
      gpioWrite(LEDG, ON);
      vTaskDelay( i*100 / portTICK_RATE_MS );
      gpioWrite(LEDG, OFF);
      vTaskDelayUntil( &xLastWakeTime,xPeriodicity);
      if(i>=10){i=0;}
   }
}


