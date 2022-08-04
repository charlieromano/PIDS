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

    size_t      length=4;
    uint8_t     data_8b[]={0x33,0x33,0x33,0x33};
    uint16_t    *data_16b=NULL;
    uint32_t    *data_32b=NULL;

    displayInit();


    gpioMap_t clk       = data_pin_array[0];
    gpioMap_t latch     = data_pin_array[1];
    gpioMap_t panel_1   = data_pin_array[2];
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

        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( 1 / portTICK_RATE_MS ) );   
        }
        }
    }
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

void gpioWriteDecoOutput(void){

    for(int i=0; i<HALF_PERIOD;i++){
            gpioToggle(deco_pin_array[0]);
    
        if((i%2)==0){        
            gpioToggle(deco_pin_array[1]);
        }
        if((i%4)==0){
            gpioToggle(deco_pin_array[2]);
        }
        if((i%8)==0){
            gpioToggle(deco_pin_array[3]);
        }
    }
}

void vTaskDisplayLED( void *pvParameters ){

    printf("vTaskDisplayLED\r\n");

    xLastWakeTimeDisplayLED = xTaskGetTickCount();

    //uint16_t output_data=0x00;
//    uint16_t output_data={0xF0,0xEF,0x00,0x0F};
    uint16_t data;
    uint32_t i=0;
    uint8_t     data_8b[]={0x33,0x66,0x33,0x33,0x67};
    
    

    displayInit();
 
    while(true){

        //printf("data: %d\r\n",((output_data++)%64));
        //data = output_data[ ++i%((int)(m_ROWS*n_COLUMNS/BIT_DIVIDER))  ];
        gpioWriteDecoOutput();
        display_send_data(data_pin_array, data_8b);

    }
}


void display_send_data(gpioMap_t *data_pin_array, uint8_t data_matrix){
/*
    gpioMap_t clk_pin       =   data_pin_array[0];//CLK;//LED2;//SRCLK;
    gpioMap_t latch_pin     =   data_pin_array[1];//G1;//LED1;//STR;
    gpioMap_t output_pin_panel_1    =   data_pin_array[2];//STR;//LED3;//SER_ARR_01;
    gpioMap_t output_pin_panel_2  =   data_pin_array[3];//STR;//LED3;//SER_ARR_01;

    uint16_t data;
    int length  = m_ROWS*n_COLUMNS/BIT_DIVIDER;
    int block   = PANEL_ROWS;

    for (int j=0 ; j< length/block;j++){

    for (int i=0 ; i< BIT_DIVIDER; i++){

        gpioWrite(output_pin_panel_1, (data_matrix[j] >> i) & (0x01));
        gpioWrite(output_pin_panel_2, (data_matrix[j+m_ROWS/DISPLAY_ROWS] >> i) & (0x01));
        gpioWrite(clk_pin, ON);
        gpioWrite(clk_pin, OFF);
    }

    if(((j+1)%(n_COLUMNS/BIT_DIVIDER))==0){

        gpioWrite(latch_pin, ON);
        gpioWrite(latch_pin, OFF);
        //scan_period();
        }
    }
*/
}

void display_clock_array(gpioMap_t *clk_array, uint8_t array_len, uint8_t period_divider ){
        
/*    for(int i=0; i<period_divider/2;i++){
        gpioToggle(clk_array[0]);
        if((i%2)==0){gpioToggle(clk_array[1]);}
        if((i%4)==0){gpioToggle(clk_array[2]);}
        if((i%8)==0){gpioToggle(clk_array[3]);}
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( (TOTAL_PERIOD/period_divider) / portTICK_RATE_MS ) );
    }
    for(int i=0; i<period_divider/2;i++){
        for(int j=0; j<array_len; j++){
            gpioWrite(clk_array[j], OFF);
        }
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( (TOTAL_PERIOD/period_divider) / portTICK_RATE_MS ) );
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

