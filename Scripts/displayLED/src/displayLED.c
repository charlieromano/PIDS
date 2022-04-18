/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/04/17
 * Version: 1.0
 ****************************************************************************/

#include <stdio.h>
#include "FreeRTOS.h"   
#include "FreeRTOSConfig.h"
#include "sapi.h"
#include "timers.h"
#include "portmap.h"



void portInit(void){
/* EDU-CIAA pinout to connector CONN_2x8 */
    CONN_2x8[0]=CONN_J4_01;
    CONN_2x8[1]=CONN_J4_02;
    CONN_2x8[2]=CONN_J4_03;
    CONN_2x8[3]=CONN_J4_04;
    CONN_2x8[4]=CONN_J4_05;
    CONN_2x8[5]=CONN_J4_06;
    CONN_2x8[6]=CONN_J4_07;
    CONN_2x8[7]=CONN_J4_08;
    CONN_2x8[8]=CONN_J4_09;
    CONN_2x8[9]=CONN_J4_10;
    CONN_2x8[10]=CONN_J4_11;
    CONN_2x8[11]=CONN_J4_12;
    CONN_2x8[12]=CONN_J4_13;
    CONN_2x8[13]=CONN_J4_14;
    CONN_2x8[14]=CONN_J4_15;
    CONN_2x8[15]=CONN_J4_16;
}


void timerCallback_displayLED(TimerHandle_t xTimerHandle){
/* displayLED clock */
    gpioToggle(SRCLK);

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