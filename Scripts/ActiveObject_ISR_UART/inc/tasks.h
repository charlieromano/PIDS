#ifndef TASKS_H
#define TASKS_H

#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "task.h"		
#include "semphr.h"		
#include "queue.h"
#include "timers.h"
#include "sapi.h"
#include "board.h"
#include "statemachine_button.h"
#include "statemachine_AB.h"

extern uint8_t data_button;
extern uint8_t data_AB;
extern sStateMachine_button 	fsmButton[]; /* State Machine struct */
extern sStateMachine_AB 		fsmMachineAB[]; /* State Machine struct */
extern xTaskHandle 	 	xTaskStateMachineHandler_button; /* RTOS task handler */
extern xTaskHandle 	 	xTaskStateMachineHandler_AB; /* RTOS task handler */
extern TimerHandle_t  	timerHandle_button; /* RTOS timer */
extern TimerHandle_t  	timerHandle_AB; /* RTOS timer */
extern QueueHandle_t 	queueHandle_button; /* RTOS queue */
extern QueueHandle_t 	queueHandle_AB; /* RTOS queue */
extern SemaphoreHandle_t xBinarySemaphore;

void vTaskTA(void *xTimerHandle);
void vTaskTB(void *xTimerHandle);
void vHandlerTask(void *pvParameters);
void vTaskEchoUART(void* pvParameters);

#endif