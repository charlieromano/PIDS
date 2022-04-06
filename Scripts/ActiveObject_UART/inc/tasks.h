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
#include "statemachine_AB.h"
#include "statemachine_Button.h"
#include "statemachine_UART.h"
#include "statemachine_PIDS.h"
#include "ISR_GPIO.h"
#include "ISR_UART.h"

#define  	QUEUE_MAX_LENGTH 	12
#define  	QUEUE_UART_RX		64
#define  	QUEUE_DATA_BUFFER   4
#define  	QUEUE_ACTIVE_OBJECT 8

uint8_t data_AB;
uint8_t dato;
uint8_t rxData;
uint8_t dataBuffer;

eSystemEvent_button 	event_button;
eSystemEvent_UART  	event_UART;
eSystemEvent_PIDS  	event_PIDS;


extern sStateMachine_AB 		fsmMachineAB[]; 
extern sStateMachine_button 	fsmButton[]; 
extern sStateMachine_button 	fsmUART[]; 
extern sStateMachine_button 	fsmPIDS[]; 

xTaskHandle 	 	xTaskStateMachineHandler_AB; 
xTaskHandle 	 	xTaskStateMachineHandler_button; 
xTaskHandle 	 	xTaskStateMachineHandler_UART; 
xTaskHandle 	 	xTaskStateMachineHandler_PIDS; 

TimerHandle_t  	timerHandle_AB; 
TimerHandle_t  	timerHandle_button; 
TimerHandle_t  	timerHandle_UART; 
TimerHandle_t  	timerHandle_PIDS; 

QueueHandle_t 	queueHandle_AB; 
QueueHandle_t 	queueHandle_button; 
QueueHandle_t 	queueHandle_UART; 
QueueHandle_t 	queueHandle_PIDS; 

QueueHandle_t 	queueUART_Rx;

SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xBinarySemaphoreUART;
SemaphoreHandle_t xMutexUART;

void vHandlerTaskGPIO(void *pvParameters);
void vHandlerTaskUART(void *pvParameters);

void vTaskTB(void *xTimerHandle);
void vTaskButton(void* pvParameters);
void vTaskUART(void* pvParameters);
#endif