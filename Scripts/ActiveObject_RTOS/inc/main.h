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
#include "statemachine_AB.h"
#include "statemachine_button.h"
#include "ISR_GPIO.h"
#include "ISR_UART.h"
#include "udf.h"

#define  	QUEUE_MAX_LENGTH 	12


DEBUG_PRINT_ENABLE;

gpioMap_t button=TEC3;
gpioMap_t led=LED;


uint8_t data_button  = 0; /* variable global */
uint8_t data_AB  = 0; /* variable global */
uint8_t dato  = 0;


#endif 
