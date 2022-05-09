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
#include "ISR_GPIO.h"
#include "ISR_UART.h"
#include "statemachine_AB.h"
#include "statemachine_Button.h"
#include "statemachine_UART.h"
#include "statemachine_PIDS.h"
#include "udf.h"
#include "portmap.h"
#include "displayLED.h"

DEBUG_PRINT_ENABLE;

gpioMap_t button=TEC3;
gpioMap_t led=LED;


#endif 
