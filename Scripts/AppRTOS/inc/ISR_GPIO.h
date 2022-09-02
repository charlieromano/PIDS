/* ISR.h */
#ifndef __ISR_GPIO_H__
#define __ISR_GPIO_H__

#include <stdio.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "semphr.h"		
#include "queue.h"      
#include "sapi.h"
#include "board.h"

extern SemaphoreHandle_t xBinarySemaphore;
extern gpioMap_t led;

void IRQ_GPIO_Init (void);

#endif 

