/*****************************************************************************
 * Copyright (c) 2022, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2022/04/17
 * Version: 1.0
 ****************************************************************************/

#include "displayLED.h"
#include "MAX7219.h"

/* Global variables */
/****************************************************************************/
#define     SCAN_PERIOD 5
#define     TIME_SLOT   10
#define     CLK_TIME    1
#define     HALF_PERIOD 4096000/100

portTickType    xLastWakeTimeDisplayLED;

bool_t      clk_state;
bool_t      timerFlag;
uint32_t    timer;
uint32_t    clock_cnt;

gpioMap_t   timer_pin=LEDB;
gpioMap_t   clk_array[]={LEDB, LED1, LED2, LED3};
gpioMap_t   deco_pin_array[] = {A, B, C, D};
gpioMap_t   data_pin_array[] = {CLK, STR, R1, R2};


/***************************************************************************/

void vTaskDisplayLED_new( void *pvParameters ){

    xLastWakeTimeDisplayLED = xTaskGetTickCount();

    size_t      length=32*8;
    uint8_t     data_8b[length];
    *data_8b=*test_data;

    uint16_t    *data_16b=NULL;
    uint32_t    *data_32b=NULL;
    TickType_t xFreq = 100;

    displayInit();

    gpioMap_t clk       = data_pin_array[0];
    gpioMap_t latch     = data_pin_array[1];
    gpioMap_t panel_1   = data_pin_array[2];
    gpioMap_t panel_2   = data_pin_array[3];
    gpioMap_t deco_A0   = deco_pin_array[0];
    gpioMap_t deco_A1   = deco_pin_array[1];
    gpioMap_t deco_A2   = deco_pin_array[2];
    gpioMap_t deco_A3   = deco_pin_array[3];
 
    while(true){

        for (int j=0;  j<= 16/*rows/panel*/;j++){
        for (int i=0 ; i< length/*data*/; i++){

        /* send_data */
        for (int k=0 ; k< 8/*bits*/; k++){
        gpioWrite(panel_1, (data_8b[i] >> k) & (0x01));
        gpioWrite(panel_2, (data_8b[i] >> k) & (0x01));
        gpioWrite(clk, ON);
        gpioWrite(clk, OFF);
        }

        /* latch */
        gpioWrite(latch, ON);
        gpioWrite(latch, OFF);

        /* deco scan */
        gpioToggle(deco_A0);
    
        if((j%2)==0){       
            gpioToggle(deco_A1);
        }
        if((j%4)==0){
            gpioToggle(deco_A2);
        }
        if((j%8)==0){
            gpioToggle(deco_A3);
        }

        vTaskDelayUntil( &xLastWakeTimeDisplayLED, xFreq/*( 10 / portTICK_RATE_MS )*/ );   
        }
        }
    }
}

void transform_data(char message[], uint8_t display_data[]){

    uint8_t data[32*8];

}

void timerCallbackDisplayLED(TimerHandle_t xTimerHandle){

    timerFlag=true;

    /* Timer */
/*    while(timerFlag){

        timer++;
        
        if((timer%10000000)==0){
            printf("Timer\r\n");
            gpioToggle(timer_pin);
        }
    }
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

void display_clock_signal(gpioMap_t clock_pin, float32_t period_ms){

    gpioWrite(clock_pin, ON);
    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );
    gpioWrite(clock_pin, OFF);
    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );

}

void display_latch_enable(gpioMap_t latch_pin, float32_t period_ms){

    gpioWrite(latch_pin, ON);
    vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( period_ms / portTICK_RATE_MS ) );
    gpioWrite(latch_pin, OFF);

}

void displayInit(void){

    gpioWrite(R1, ON);
    gpioWrite(R2, ON);
    gpioWrite(G1, OFF);
    gpioWrite(G2, OFF);

    gpioWrite(deco_pin_array[0], OFF);
    gpioWrite(deco_pin_array[1], OFF);
    gpioWrite(deco_pin_array[2], OFF);
    gpioWrite(deco_pin_array[3], OFF);

    gpioWrite(data_pin_array[0], OFF);
    gpioWrite(data_pin_array[1], OFF);
    gpioWrite(data_pin_array[2], OFF);
    gpioWrite(data_pin_array[3], OFF);

}

