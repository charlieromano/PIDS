/* ISR.h */
#ifndef ISR_GPIO_H
#define ISR_GPIO_H

#include <stdio.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "semphr.h"		
#include "queue.h"      
#include "sapi.h"
#include "board.h"
#include "timers.h"

/* State Machine Button*/
extern	SemaphoreHandle_t xBinarySemaphore; 	/* ROTS semaphore */
extern 	TimerHandle_t	  timerHandle_button; 	/* RTOS timer */
extern 	QueueHandle_t	  queueHandle_button; 	/* RTOS queue */
extern	void	timerCallback_button(TimerHandle_t xTimerHandle); /* RTOS timer callback */
extern gpioMap_t button;
extern gpioMap_t led;

void IRQ_GPIO_Init (void);

#endif 

