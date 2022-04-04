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


extern sStateMachine_AB 		fsmMachineAB[]; 
extern sStateMachine_button 	fsmButton[]; 
extern sStateMachine_button 	fsmUART[]; 

extern xTaskHandle 	 	xTaskStateMachineHandler_AB; 
extern xTaskHandle 	 	xTaskStateMachineHandler_button; 
extern xTaskHandle 	 	xTaskStateMachineHandler_UART; 

extern TimerHandle_t  	timerHandle_AB; 
extern TimerHandle_t  	timerHandle_button; 
extern TimerHandle_t  	timerHandle_UART; 

extern QueueHandle_t 	queueHandle_AB; 
extern QueueHandle_t 	queueHandle_button; 
extern QueueHandle_t 	queueHandle_UART; 

extern SemaphoreHandle_t xBinarySemaphore;
extern SemaphoreHandle_t xBinarySemaphoreUART;
extern SemaphoreHandle_t xMutexUART;

void vHandlerTaskGPIO(void *pvParameters);
void vHandlerTaskUART(void *pvParameters);

void vTaskTB(void *xTimerHandle);
void vTaskButton(void* pvParameters);
void vTaskUART(void* pvParameters);

#endif