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
#include "ISR_UART.h"

extern uint8_t data_button;
extern uint8_t data_AB;
extern sStateMachine_button 	fsmButton[]; /* State Machine struct */
extern sStateMachine_AB 		fsmMachineAB[]; /* State Machine struct */
extern xTaskHandle 	 	xTaskStateMachineHandlerButton; /* RTOS task handler */
extern xTaskHandle 	 	xTaskStateMachineHandlerAB; /* RTOS task handler */
extern TimerHandle_t  	timerHandleButton; /* RTOS timer */
extern TimerHandle_t  	timerHandleAB; /* RTOS timer */
extern QueueHandle_t 	queueHandleButton; /* RTOS queue */
extern QueueHandle_t 	queueHandleAB; /* RTOS queue */
extern SemaphoreHandle_t xBinarySemaphore;
extern SemaphoreHandle_t xBinarySemaphoreUART;
extern   uint8_t dato;

uint8_t data_AB;
uint8_t dato;
uint8_t rxData;
uint8_t data_rx;
uint8_t data_tx;

eSystemEvent_button 	event_button;
//eSystemEvent_UART  		event_UART;


extern sStateMachine_AB 		fsmMachineAB[]; 
extern sStateMachine_button 	fsmButton[]; 
//extern sStateMachine_button 	fsmUART[]; 

xTaskHandle 	 	xTaskStateMachineHandler_button; 
//xTaskHandle 	 	xTaskStateMachineHandler_UART; 

TimerHandle_t  	timerHandle_button; 
//TimerHandle_t  	timerHandle_UART; 

QueueHandle_t 	queueHandleButton; 
QueueHandle_t 	queueHandleUART; 
QueueHandle_t 	dataBufferQueue;

SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xBinarySemaphoreUART;
SemaphoreHandle_t xMutexUART;


void vHandlerTaskGPIO(void *pvParameters);
void vHandlerTaskUART(void *pvParameters);
void vHandlerTaskAB(void *pvParameters);

void vTaskButton(void* pvParameters);
void vTaskUART(void* pvParameters);
void vTaskUART_buffer(void* pvParameters);


void timerCallbackUART(TimerHandle_t xTimerHandle);


/* State Machine AB*/
void vTaskAB(void *xTimerHandle);
void timerCallbackAB(TimerHandle_t xTimerHandle);
void timerCallbackButton(TimerHandle_t xTimerHandle);

QueueHandle_t 	queueHandleAB; 
TimerHandle_t  	timerHandleAB; 
xTaskHandle	 	xTaskStateMachineHandlerAB; 

#endif