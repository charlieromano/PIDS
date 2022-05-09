/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/04/17
 * Version: 1.0
 ****************************************************************************/

#include "displayLED.h"

uint8_t timer_cnt_CLK, timer_cnt_STR;
bool_t clk_state;

void timerCallback_displayCLK(TimerHandle_t xTimerHandle){
/* displayLED clock */
    
    clk_state = !clk_state;
    //gpioWrite(CONN_J4_16, clk_state);
    gpioWrite(SRCLK, clk_state);
    gpioWrite(SER_ARR_01, clk_state);

}

void timerCallback_displaySTR(TimerHandle_t xTimerHandle){
/* displayLED clock */
/*
    timer_cnt_STR++;
    printf("STR:%d",timer_cnt_STR);
    if(timer_cnt_STR<=STR_DUTY_CYCLE_PERIOD){
        if(timer_cnt_STR<=STR_DUTY_CYCLE_ON)
            gpioWrite(SER_ARR_01, ON);
        else
            gpioWrite(SER_ARR_01, OFF);
    }
    else
        timer_cnt_STR=0;
*/
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