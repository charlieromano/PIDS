#ifndef TASKS_H
#define TASKS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "task.h"		
#include "semphr.h"		
#include "queue.h"
#include "timers.h"
#include "sapi.h"
#include "board.h"
#include "statemachine_Button.h"
#include "statemachine_AB.h"
#include "ISR_UART.h"

extern	uint8_t data_AB;
extern  uint8_t dato;
extern  uint8_t rxData;
extern  uint8_t dataBuffer;
extern eSystemEvent_button event_button;


extern sStateMachine_button 	fsmButton[]; /* State Machine struct */
extern sStateMachine_AB 		fsmMachineAB[]; /* State Machine struct */

extern xTaskHandle 	 	xTaskStateMachineHandler_button; /* RTOS task handler */
extern xTaskHandle 	 	xTaskStateMachineHandler_AB; /* RTOS task handler */

extern TimerHandle_t  	timerHandle_button; /* RTOS timer */
extern TimerHandle_t  	timerHandle_AB; /* RTOS timer */

extern QueueHandle_t 	queueHandle_button; /* RTOS queue */
extern QueueHandle_t 	queueHandle_AB; /* RTOS queue */

extern SemaphoreHandle_t xBinarySemaphore;
extern SemaphoreHandle_t xBinarySemaphoreUART;
extern SemaphoreHandle_t xMutexUART;

void vTaskButton(void* pvParameters);
void vTaskTB(void *xTimerHandle);
void vHandlerTask(void *pvParameters);
void vTaskUART(void* pvParameters);
void vTaskProcessData(void* pvParameters);

#endif