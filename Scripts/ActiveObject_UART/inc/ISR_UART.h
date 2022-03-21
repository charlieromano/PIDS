/* ISR_UART.h */
#ifndef ISR_UART_H
#define ISR_UART_H

#include <stdio.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "semphr.h"		
#include "queue.h"      
#include "sapi.h"
#include "board.h"
#include "sapi.h"
#include "sapi_uart.h"

#define UART_BAUD_RATE 115200

void IRQ_UART_Init( void );
void UART_IRQHandler( void );

extern SemaphoreHandle_t xBinarySemaphore;
extern SemaphoreHandle_t xBinarySemaphoreUART;

#endif