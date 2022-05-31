/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/04/17
 * Version: 1.0
 ****************************************************************************/

#include "displayLED.h"

#define CLK_BIT_LENGTH  16
#define CLK_PERIOD      64

uint8_t timer_cnt_CLK, timer_cnt_STR;
bool_t clk_state;
uint8_t clock_cnt;

#Global variable 
portTickType xLastWakeTimeDisplayLED;


void vTaskFunction( void *pvParameters ){

    xLastWakeTimeDisplayLED = xTaskGetTickCount();

    int i;
    uint16_t data_out=0b00001000;

    gpioMap_t output_pin    =   SER_ARR_01;
    gpioMap_t clk_pin       =   SRCLK;
    gpioMap_t latch_pin     =   STR;
    uint8_t clk_period      =   1;

    while(true){
        for (int j=0; j<LED_MATRIX_HEIGHT; j++){
            for (int i=0 ; i<LED_MATRIX_WIDTH; i++)
            {
                output_pin = (output_data >> i) & (0x01);
                clock_signal(clk_pin, 2*clk_period );
            }
            latch_enable(latch_pin, clk_period); // Data finally submitted
            deco_signal(j, LED_MATRIX_FRAME_RATE/LED_MATRIX_HEIGHT);
        }
    }
}


void clock_signal(gpioMap_t clk_pin, uint8_t period_ms){

    gpioWrite(clk_pin, ON);
    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );
    gpioWrite(clk_pin, OFF);
    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );

}

void latch_enable(gpioMap_t latch_pin, uint8_t period_ms){

    gpioWrite(latch_pin, ON);
    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );
    gpioWrite(latch_pin, OFF);

}

void deco_signal(uint8_t code, uint8_t period_ms){

    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );

    switch(code){
    case 0:
        gpioWrite(DECO_A0,OFF);
        gpioWrite(DECO_A1,OFF);
        gpioWrite(DECO_A2,OFF);
    case 1:
        gpioWrite(DECO_A0,OFF);
        gpioWrite(DECO_A1,OFF);
        gpioWrite(DECO_A2,ON);
    case 2:
        gpioWrite(DECO_A0,OFF);
        gpioWrite(DECO_A1,ON);
        gpioWrite(DECO_A2,OFF);
    case 3:
        gpioWrite(DECO_A0,OFF);
        gpioWrite(DECO_A1,ON);
        gpioWrite(DECO_A2,ON);            
    case 4:
        gpioWrite(DECO_A0,ON);
        gpioWrite(DECO_A1,OFF);
        gpioWrite(DECO_A2,OFF);
    case 5:
        gpioWrite(DECO_A0,ON);
        gpioWrite(DECO_A1,OFF);
        gpioWrite(DECO_A2,ON);
    case 6:
        gpioWrite(DECO_A0,ON);
        gpioWrite(DECO_A1,ON);
        gpioWrite(DECO_A2,OFF);
    case 7:
        gpioWrite(DECO_A0,ON);
        gpioWrite(DECO_A1,ON);
        gpioWrite(DECO_A2,ON);
    default:
        gpioWrite(LEDR, ON);
    }
}
 

void portInit(void){
/* EDU-CIAA pinout to connector CONN_2x8 */
    gpioConfig( CONN_J4_01, GPIO_OUTPUT );
    gpioConfig( CONN_J4_02, GPIO_OUTPUT );
    gpioConfig( CONN_J4_03, GPIO_OUTPUT );
    gpioConfig( CONN_J4_04, GPIO_OUTPUT );
    gpioConfig( CONN_J4_05, GPIO_OUTPUT );
    gpioConfig( CONN_J4_06, GPIO_OUTPUT );
    gpioConfig( CONN_J4_07, GPIO_OUTPUT );
    gpioConfig( CONN_J4_08, GPIO_OUTPUT );
    gpioConfig( CONN_J4_09, GPIO_OUTPUT );
    gpioConfig( CONN_J4_10, GPIO_OUTPUT );
    gpioConfig( CONN_J4_11, GPIO_OUTPUT );
    gpioConfig( CONN_J4_12, GPIO_OUTPUT );
    gpioConfig( CONN_J4_13, GPIO_OUTPUT );
    gpioConfig( CONN_J4_14, GPIO_OUTPUT );
    gpioConfig( CONN_J4_15, GPIO_OUTPUT );
    gpioConfig( CONN_J4_16, GPIO_OUTPUT );

}

void initDisplayTest(void){
    gpioWrite(DECO_A0, ON);
    gpioWrite(DECO_A1, ON);
    gpioWrite(DECO_A2, ON);
    gpioWrite(DECO_E2_E2, ON);
    gpioWrite(DECO_E3_E1, ON);
    gpioWrite(SER_ARR_01, ON);
}

/*
#define DECO_A0     HC245_A1_R
#define DECO_A1     HC245_A2_R
#define DECO_A2     HC245_A3_R
#define DECO_E2_E2  HC245_A5_R
#define DECO_E3_E1  HC245_A4_R
#define SER_ARR_01  HC245_B1_L
#define SER_ARR_02  HC245_B3_L
#define SRCLK       HC245_B5_L
*/



