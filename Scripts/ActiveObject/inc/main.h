#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "task.h"		
#include "semphr.h"		
#include "queue.h"      
#include "sapi.h"
#include "board.h"
#include "tasks.h"
#include "timers.h"
#include "statemachine.h"
#include "udf.h"

#define  	QUEUE_MAX_LENGTH 	12

DEBUG_PRINT_ENABLE;
uint8_t data  = 0; /* variable global */

xTaskHandle 	xTaskStateMachineHandler; /* RTOS task handler */
TimerHandle_t  	timerHandle; /* RTOS timer */
QueueHandle_t 	queueHandle; /* RTOS queue */

void timerCallback(TimerHandle_t xTimerHandle); /* RTOS timer */

#endif 
