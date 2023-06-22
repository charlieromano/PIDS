/* ISR_UART.h */
#ifndef __ISR_UART_H__
#define __ISR_UART_H__

#include <stdio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"   
#include "sapi.h"
#include "board.h"
#include "semphr.h"
#include "statemachine_UART.h"

#define UART_BAUD_RATE 115200
#define UART_QUEUE_WAITING_TICKS 0

void IRQ_UART_Init( void );
void UART_ISR_Handler( void * );

extern SemaphoreHandle_t 	xMutexUART;
extern SemaphoreHandle_t 	xBinarySemaphoreUART;
extern QueueHandle_t        queueHandle_UART; 

#endif