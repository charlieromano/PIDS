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
#include "statemachine_Button.h"
#include "statemachine_UART.h"
#include "ISR_GPIO.h"
#include "ISR_UART.h"
#include "udf.h"

#define  	QUEUE_MAX_LENGTH 	12
#define  	QUEUE_UART_RX		64
#define  	QUEUE_DATA_BUFFER   4
#define  	QUEUE_ACTIVE_OBJECT 8


DEBUG_PRINT_ENABLE;

gpioMap_t button=TEC1;

/* global variables */
uint8_t dato  = 0;
uint8_t rxData = 0;
uint8_t dataBuffer = 0;

/* state machines AO queue variables */
eSystemEvent_button event_button;

/* RTOS task handlers */
xTaskHandle 	xTaskStateMachineHandler_button; 
xTaskHandle 	xTaskStateMachineHandler_UART; 
xTaskHandle 	xTaskStateMachineHandler_AB; 

/* RTOS queues */
QueueHandle_t 	queueUART_Rx; 
QueueHandle_t 	queueHandle_AB; 
QueueHandle_t	queueHandle_button; 	
QueueHandle_t 	queueHandle_UART;

/* RTOS semaphores and mutexes */
SemaphoreHandle_t xMutexUART;
SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xBinarySemaphoreUART;

/* RTOS timers */
TimerHandle_t  	timerHandle_AB; 
TimerHandle_t	timerHandle_button; 
TimerHandle_t	timerHandle_UART; 

/* timer callbacks */
void 	timerCallback_AB(TimerHandle_t xTimerHandle);
void	timerCallback_button(TimerHandle_t xTimerHandle); 
void	timerCallback_UART(TimerHandle_t xTimerHandle); 

/* ISR */







#endif 
