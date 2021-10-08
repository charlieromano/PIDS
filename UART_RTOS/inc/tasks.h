#ifndef TASKS_H
#define TASKS_H

#include "FreeRTOS.h"   //Motor del OS
#include "FreeRTOSConfig.h"
#include "task.h"		//Api de control de tareas y temporizaciÃ³n
#include "semphr.h"		//Api de sincronizaciÃ³n (sem y mutex)
#include "queue.h"      //Api de colas
#include "sapi.h"
#include "board.h"
#include "structs.h"

#define ANTIREBOTE_MS 20
#define CANT_LEDS 4

extern SemaphoreHandle_t mutexUART;
extern SemaphoreHandle_t mutexSPI;

void vTaskReadUART(void* taskParamPtr );
void vTaskWriteUART(void* taskParamPtr );

#endif