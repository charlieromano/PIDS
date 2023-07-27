/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/


#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define     QUEUE_MAX_LENGTH    12
#define     QUEUE_UART_RX       64
#define     QUEUE_DATA_BUFFER   4
#define     QUEUE_ACTIVE_OBJECT 8

extern sStateMachine_AB         fsmMachineAB[]; 
extern sStateMachine_button     fsmButton[]; 
extern sStateMachine_displayLed fsmDisplayLed[]; 
extern sStateMachine_button     fsmUART[]; 
extern sStateMachine_button     fsmPIDS[]; 

void timerCallback_button(TimerHandle_t xTimerHandle);  
void timerCallback_AB(TimerHandle_t xTimerHandle);
void timerCallback_displayLed(TimerHandle_t xTimerDisplayHandle);
void timerCallback_UART(TimerHandle_t xTimerHandle);
void timerCallback_PIDS(TimerHandle_t xTimerHandle);

void vHandlerTaskGPIO(void* pvParameters);
void vHandlerTaskUART(void *pvParameters);

void myTask( void* taskParmPtr );  
void vTaskButton(void* pvParameters);
void vTaskAB(void *xTimerHandle);
void vTaskDisplayLed(void *xTimerDisplayHandle);
void vTaskUART(void* pvParameters);
void vTaskUART_buffer(void* pvParameters);
void vTaskTest(void *xTimerDisplayHandle);
void vTaskPIDS(void* pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* __USER_TASKS_H__ */
