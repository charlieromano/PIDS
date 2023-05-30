/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*=====[Inclusions of public function dependencies]==========================*/

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
#include "ISR_UART.h"
#include "ISR_GPIO.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
#define     QUEUE_MAX_LENGTH    12
#define     QUEUE_UART_RX       64
#define     QUEUE_DATA_BUFFER   4
#define     QUEUE_ACTIVE_OBJECT 8
/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

extern SemaphoreHandle_t    xBinarySemaphore;
extern SemaphoreHandle_t    xMutexUART;
extern QueueHandle_t        queueHandle_button;
extern QueueHandle_t        queueHandle_AB;
extern QueueHandle_t        queueHandle_displayLed;
extern QueueHandle_t        queueHandle_UART; 
extern QueueHandle_t        dataBufferQueue;

extern sStateMachine_AB         fsmMachineAB[]; 
extern sStateMachine_button     fsmButton[]; 
extern sStateMachine_displayLed fsmDisplayLed[]; 
extern sStateMachine_button     fsmUART[]; 
extern sStateMachine_button     fsmPIDS[]; 

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
extern uint8_t     data_AB;
extern uint8_t     data_display;
extern uint8_t data_AB;
extern uint8_t dato;
extern uint8_t rxData;
extern uint8_t data_rx;
extern uint8_t data_tx;
extern uint8_t data_array[DATA_ARRAY_LENGTH];
extern uint8_t data_array_copy[DATA_ARRAY_LENGTH];
extern uint8_t output_array_copy[DATA_ARRAY_LENGTH];

/*=====[Prototypes (declarations) of public functions]=======================*/

void timerCallback_button(TimerHandle_t xTimerHandle);  
void timerCallback_AB(TimerHandle_t xTimerHandle);
void timerCallback_displayLed(TimerHandle_t xTimerDisplayHandle);
void timerCallback_UART(TimerHandle_t xTimerHandle);

void vHandlerTaskGPIO(void* pvParameters);
void vHandlerTaskUART(void *pvParameters);

void myTask( void* taskParmPtr );  // Task declaration
void vTaskButton(void* pvParameters);
void vTaskAB(void *xTimerHandle);
void vTaskDisplayLed(void *xTimerDisplayHandle);
void vTaskUART(void* pvParameters);
void vTaskUART_buffer(void* pvParameters);
void vTaskTest(void *xTimerDisplayHandle);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __USER_TASKS_H__ */
