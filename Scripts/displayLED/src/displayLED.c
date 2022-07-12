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
portTickType    xLastWakeTimeDisplayLED;

bool_t      clk_state;
bool_t      timerFlag;
uint32_t    timer;
uint32_t    clock_cnt;

gpioMap_t   timer_pin=LEDG;
gpioMap_t   clk_array[]={LEDB, LED1, LED2, LED3};
gpioMap_t   deco_pin_array[] = {A, B, C, D};
gpioMap_t   data_pin_array[] = {CLK, STR, R1, R2};

/***************************************************************************/

void timerCallbackDisplayLED(TimerHandle_t xTimerHandle){

    /* Timer */
    while(timerFlag){
        timer++;
        if((timer%2)==0){
            gpioToggle(timer_pin);
        }
    }
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

#define     SCAN_PERIOD 5
#define     TIME_SLOT   10
#define     CLK_TIME    1
#define     HALF_PERIOD 4096000/100

void vTaskDisplayLED( void *pvParameters ){

    printf("vTaskDisplayLED\r\n");

    xLastWakeTimeDisplayLED = xTaskGetTickCount();

    uint16_t output_data=0x00;

    displayInit();
 
    while(true){

        printf("data: %d\r\n",((output_data++)%64));

        gpioWriteDecoOutput();
        display_send_data(data_pin_array, ((output_data++)%64));
        //vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( SCAN_PERIOD / portTICK_RATE_MS ) );
    }
}


void display_send_data(gpioMap_t *data_pin_array, uint8_t data){

    gpioMap_t clk_pin       =   data_pin_array[0];//CLK;//LED2;//SRCLK;
    gpioMap_t latch_pin     =   data_pin_array[1];//G1;//LED1;//STR;
    gpioMap_t output_pin    =   data_pin_array[2];//STR;//LED3;//SER_ARR_01;
    gpioMap_t output_pin_2  =   data_pin_array[3];//STR;//LED3;//SER_ARR_01;

    for (int i=0 ; i<PANEL_COLUMNS; i++){

        printf("loop: i=%d \r\n",i);

        gpioWrite(output_pin, 0xFF);//(data >> (i%8)) & (0x01));
        gpioWrite(output_pin_2, 0xFF);//(data >> (i%8)) & (0x01));
        
        gpioWrite(clk_pin, ON);
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( CLK_TIME / portTICK_RATE_MS ) );
        gpioWrite(clk_pin, OFF);
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( CLK_TIME / portTICK_RATE_MS ) );

    }

    gpioWrite(latch_pin, ON);
    gpioWrite(latch_pin, OFF);

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
