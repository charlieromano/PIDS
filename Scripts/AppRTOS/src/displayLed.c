/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/04
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "displayLed.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

extern portTickType    xLastWakeTimeDisplayLed;

/*=====[Definitions of public global variables]==============================*/

bool_t      timerFlag;
uint32_t    timer;
uint32_t    clock_cnt;
TickType_t  xFreq = 5;

gpioMap_t   timer_pin=LEDB;
gpioMap_t   clk_array[]={LEDB, LED1, LED2, LED3};
gpioMap_t   deco_pin_array[] = {A, B, C, D};
gpioMap_t   data_pin_array[] = {CLK, STR, R1, R2};

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

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

void vTaskDisplayLed( void *pvParameters ){

    xLastWakeTimeDisplayLed = xTaskGetTickCount();

    printf( "displayLED with freeRTOS y sAPI.\r\n" );

    size_t      length=32*8;
    //uint8_t     data_8b[length];
    uint8_t     data_8b[] = {
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00, 
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00, 
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00, 
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00
    };//*test_data;

    uint16_t    *data_16b=NULL;
    uint32_t    *data_32b=NULL;

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
  
          for (int j=0;  j<= 16 ;j++){ // 16 rows/panel
              for (int i=0 ; i< length; i++){ // length data
            // send_data 
            for (int k=0 ; k< 8; k++){ // k< 8bits
                gpioWrite(panel_1, (data_8b[i] >> k) & (0x01));
                gpioWrite(panel_2, (data_8b[i] >> k) & (0x01));
                gpioWrite(clk, ON);
                gpioWrite(clk, OFF);
            }

            // latch 
            gpioWrite(latch, ON);
            gpioWrite(latch, OFF);

            // deco scan 
            gpioToggle(deco_A0);
        
            if((j%2)==0){ gpioToggle(deco_A1); }
            if((j%4)==0){ gpioToggle(deco_A2); }
            if((j%8)==0){ gpioToggle(deco_A3); }

            vTaskDelayUntil( &xLastWakeTimeDisplayLed, xFreq);
            //( 10 / portTICK_RATE_MS ) );
            }
        }
    }
/*
*/
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
