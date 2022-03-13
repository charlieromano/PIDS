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
#include "statemachine_AB.h"
#include "statemachine_button.h"
#include "ISR_GPIO.h"
#include "ISR_UART.h"
#include "udf.h"

#define  	QUEUE_MAX_LENGTH 	12

DEBUG_PRINT_ENABLE;

gpioMap_t button=TEC2;

uint8_t data_button  = 0; /* variable global */
uint8_t data_AB  = 0; /* variable global */

/* RTOS task handlers */
xTaskHandle 	xTaskStateMachineHandler_button; 
xTaskHandle 	xTaskStateMachineHandler_AB; 

/* State Machine Button*/
TimerHandle_t  	timerHandle_button; /* RTOS timer */
QueueHandle_t 	queueHandle_button; /* RTOS queue */
void timerCallback_button(TimerHandle_t xTimerHandle); /* RTOS timer */

/* State Machine AB*/
TimerHandle_t  	timerHandle_AB; /* RTOS timer */
QueueHandle_t 	queueHandle_AB; /* RTOS queue */
void timerCallback_AB(TimerHandle_t xTimerHandle);/* RTOS timer */


SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xBinarySemaphoreUART;

#endif 
