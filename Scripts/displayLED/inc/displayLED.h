//displayLED.h

#ifndef DISPLAYLED_H
#define DISPLAYLED_H

#include <stdio.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "sapi.h"
#include "timers.h"
#include "portmap.h"

#define LED_MATRIX_WIDTH		64
#define LED_MATRIX_HEIGHT		32
#define LED_MATRIX_FRAME_RATE 	50

#define LED_MATRIX_ROWS		 	LED_MATRIX_HEIGHT
#define LED_MATRIX_COLUMNS	 	LED_MATRIX_WIDTH
#define LED_MATRIX_LATCH_PERIOD

#define     TOTAL_PERIOD    		20 //ms
#define 	TIMER_DISPLAY_LED_MS 	50//ms

void portInit(void);
void initDisplayTest(void);

TimerHandle_t  	timerHandleDisplayLED; /* RTOS timer */
void timerCallbackDisplayLED(TimerHandle_t xTimerHandle);

void display_send_data(gpioMap_t *data_pin_array, unsigned int data);
void display_clock_signal(gpioMap_t clock_pin, float32_t period_ms);
void display_latch_enable(gpioMap_t latch_pin, float32_t period_ms);
void display_deco_signal(void);
void display_clock_array(gpioMap_t *clk_array, uint8_t array_len, uint8_t clk_number );
void gpioWriteDecoOutput(uint8_t output);
void vTaskDisplayLED(void* pvParameters);


#endif
