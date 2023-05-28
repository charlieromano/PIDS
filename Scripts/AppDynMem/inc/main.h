/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __MAIN_H__
#define __MAIN_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "sapi.h"
#include "userTasks.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

gpioMap_t button=TEC3;
gpioMap_t led=LEDR;

uint8_t             timer_cnt;
bool                timer_flag;

uint8_t             data_AB;

TimerHandle_t       timerHandle_AB; 
TimerHandle_t       timerHandle_button; 

QueueHandle_t       queueHandle_button;
QueueHandle_t       queueHandle_AB;

xTaskHandle         xTaskStateMachineHandler_button; 
xTaskHandle         xTaskStateMachineHandler_AB; 
xTaskHandle         xTaskDisplayLedHandler; 
xTaskHandle         xTaskReadSerialHandler; 
xTaskHandle         xTaskWriteSerialHandler; 


SemaphoreHandle_t   xBinarySemaphore;
SemaphoreHandle_t   xMutexUART;

portTickType    xLastWakeTimeDisplayLed;

/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __APPRTOS_H__ */
