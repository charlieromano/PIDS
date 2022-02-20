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
#include "statemachine.h"

extern uint8_t data;
extern sStateMachine 	fsmTest[]; /* State Machine struct */
extern xTaskHandle 	 	xTaskStateMachineHandler; /* RTOS task handler */
extern TimerHandle_t  	timerHandle; /* RTOS timer */
extern QueueHandle_t 	queueHandle; /* RTOS queue */

void vTaskStateMachine(void *pvParameters);
void vTaskTA(void *xTimerHandle);

#endif