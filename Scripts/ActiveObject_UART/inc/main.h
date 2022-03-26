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
#include "statemachine_GPIO.h"
#include "statemachine_UART.h"
#include "ISR_GPIO.h"
#include "ISR_UART.h"
#include "udf.h"

#define  	QUEUE_MAX_LENGTH 	12
#define  	QUEUE_UART_RX		64
#define  	QUEUE_DATA_BUFFER   4
#define  	QUEUE_ACTIVE_OBJECT 8


DEBUG_PRINT_ENABLE;

gpioMap_t button=TEC2;

uint8_t data_button  = 0; /* variable global */
uint8_t data_AB  = 0; /* variable global */
uint8_t dato  = 0;
uint8_t rxData = 0;
uint8_t dataBuffer = 0;

/* RTOS task handlers */
xTaskHandle 	xTaskStateMachineHandler_button; 
xTaskHandle 	xTaskStateMachineHandler_AB; 

/* State Machine Button*/
SemaphoreHandle_t xBinarySemaphore; 	/* ROTS semaphore */
TimerHandle_t	  timerHandle_button; 	/* RTOS timer */
QueueHandle_t	  queueHandle_button; 	/* RTOS queue */
void	timerCallback_button(TimerHandle_t xTimerHandle); /* RTOS timer callback */

void IRQ_GPIO_Init (void);

/* State Machine AB*/
TimerHandle_t  	timerHandle_AB; /* RTOS timer */
QueueHandle_t 	queueHandle_AB; /* RTOS queue */
void timerCallback_AB(TimerHandle_t xTimerHandle);/* RTOS timer */


SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xBinarySemaphoreUART;


QueueHandle_t 	queueUART_Rx; /* RTOS queue for UART*/
QueueHandle_t 	queueHandleUART_AO; /* RTOS queue for UART Active Object*/


#endif 
