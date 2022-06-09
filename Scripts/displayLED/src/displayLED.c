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
uint8_t clock_cnt;

/* Global variables */
portTickType xLastWakeTimeDisplayLED;


void vTaskDisplayLED( void *pvParameters ){

    printf("vTaskDisplayLED\r\n");

    xLastWakeTimeDisplayLED = xTaskGetTickCount();

    uint16_t output_data=0x24;
 
    //gpioWrite(R1, ON);
    //gpioWrite(R2, OFF);
    //gpioWrite(G1, ON);
    //gpioWrite(G2, OFF);


    gpioMap_t clk_array[]={LEDB, LED1, LED2, LED3};

    while(true){

//        display_send_data(output_data);
        display_clock_array(clk_array, 4, 64);

    }
}

#define     TOTAL_PERIOD    4000 //ms



void display_clock_array(gpioMap_t *clk_array, uint8_t array_len, uint8_t clk_number ){

    for(int i=0; i<array_len; i++){
        gpioWrite(clk_array[i], ON);
    }

    
    for(int i=0; i<clk_number/2;i++){
        gpioToggle(clk_array[0]);
        if((i%2)==0){gpioToggle(clk_array[1]);}
        if((i%4)==0){gpioToggle(clk_array[2]);}
        if((i%8)==0){gpioToggle(clk_array[3]);}
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( (int)(TOTAL_PERIOD/clk_number) / portTICK_RATE_MS ) );
    }
    for(int i=0; i<clk_number/2;i++){
        for(int j=0; j<array_len; j++){
            gpioWrite(clk_array[j], ON);
        }
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( (int)(TOTAL_PERIOD/clk_number) / portTICK_RATE_MS ) );
    }

}

void display_send_data(unsigned int data){

    gpioMap_t output_pin    =   STR;//LED3;//SER_ARR_01;
    gpioMap_t clk_pin       =   CLK;//LED2;//SRCLK;
    gpioMap_t latch_pin     =   G1;//LED1;//STR;

    int    timer_ms =   4;


    for (int j=0; j<LED_MATRIX_ROWS; j++){

        for (int i=0 ; i<LED_MATRIX_COLUMNS; i++){

            gpioWrite(output_pin, (data >> i) & (0x01));
            display_clock_signal(clk_pin, timer_ms);

        }

        display_latch_enable(latch_pin, timer_ms); 
        display_deco_signal();
    }
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

void display_deco_signal(void){

    for(int i=0; i<LED_MATRIX_ROWS; i++){
        gpioWriteDecoOutput(i);
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( (LED_MATRIX_FRAME_RATE/LED_MATRIX_HEIGHT) / portTICK_RATE_MS ) );
    }

}





void gpioWriteDecoOutput(uint8_t output){

    switch(output){
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



