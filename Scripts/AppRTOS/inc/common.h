/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2023/07/26
 * Version: 1.0
 *===========================================================================*/

#ifndef __COMMON_H__
#define __COMMON_H__

#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"

#include "statemachine_AB.h"
#include "statemachine_button.h"
#include "statemachine_displayLed.h"
#include "statemachine_UART.h"
#include "statemachine_PIDS.h"

#include "ISR_UART.h"
#include "ISR_GPIO.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SemaphoreHandle_t    xBinarySemaphore;
extern SemaphoreHandle_t    xMutexUART;

extern QueueHandle_t        queueHandle_button;
extern QueueHandle_t        queueHandle_AB;
extern QueueHandle_t        queueHandle_displayLed;
extern QueueHandle_t        queueHandle_UART; 
extern QueueHandle_t        queueHandle_PIDS; 
extern QueueHandle_t        dataBufferQueue;

extern xTaskHandle         xTaskStateMachineHandler_AB; 
extern xTaskHandle         xTaskStateMachineHandler_button; 
extern xTaskHandle         xTaskStateMachineHandler_displayLed; 
extern xTaskHandle         xTaskStateMachineHandler_UART; 
extern xTaskHandle         xTaskStateMachineHandler_PIDS; 

extern TimerHandle_t        timerHandle_AB; 
extern TimerHandle_t        timerHandle_button; 
extern TimerHandle_t        timerHandle_displayLed; 

extern uint8_t     timer_cnt; 
extern bool        timer_flag;

extern volatile bool_t uart_timer_flag;
extern volatile bool_t pids_timer_flag;


#ifdef __cplusplus
}
#endif

#endif 
