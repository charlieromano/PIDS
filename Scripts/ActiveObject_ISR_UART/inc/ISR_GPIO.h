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

extern SemaphoreHandle_t xBinarySemaphore;

void IRQ_GPIO_Init (void);

#endif 

