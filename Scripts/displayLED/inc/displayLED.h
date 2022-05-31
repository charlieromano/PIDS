//displayLED.h

#ifndef DISPLAYLED_H
#define DISPLAYLED_H

#include <stdio.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "sapi.h"
#include "timers.h"
#include "portmap.h"


#define DISPLAY_LED_CLK 	2 //ms
#define DISPLAY_LED_STR		3000
#define CLK_DUTY_CYCLE_ON  		7
#define CLK_DUTY_CYCLE_OFF  	1
#define CLK_DUTY_CYCLE_PERIOD  	64 
#define STR_DUTY_CYCLE_ON  		2
#define STR_DUTY_CYCLE_OFF  	5
#define STR_DUTY_CYCLE_PERIOD  	7 

#define PERIOD_C	100

#define LED_MATRIX_WIDTH		64
#define LED_MATRIX_HEIGHT		32
#define LED_MATRIX_FRAME_RATE 	50


void portInit(void);
void initDisplayTest(void);
void timerCallback_displayCLK(TimerHandle_t xTimerHandle);
void timerCallback_displaySTR(TimerHandle_t xTimerHandle);

void clock_signal(void);
void latch_enable(void);
void send_data(unsigned int data_out);

void deco_signal(void);

#endif
