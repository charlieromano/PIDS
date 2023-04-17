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
extern SemaphoreHandle_t   xMutexUART;

/*=====[Definitions of public global variables]==============================*/

bool_t      timerFlag;
uint32_t    timer;
uint32_t    clock_cnt;
TickType_t  xFreq = 10;

gpioMap_t   timer_pin=LEDB;
gpioMap_t   clk_array[]={LEDB, LED1, LED2, LED3};
gpioMap_t   deco_pin_array[] = {A, B, C, D};
gpioMap_t   data_pin_array[] = {CLK, STR, R1, R2};

gpioMap_t clk       = data_pin_array[0];
gpioMap_t latch     = data_pin_array[1];
gpioMap_t panel_1   = data_pin_array[2];
gpioMap_t panel_2   = data_pin_array[3];
gpioMap_t deco_A0   = deco_pin_array[0];
gpioMap_t deco_A1   = deco_pin_array[1];
gpioMap_t deco_A2   = deco_pin_array[2];
gpioMap_t deco_A3   = deco_pin_array[3];


uint8_t new_ascii[855]={
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //
    0x21, 0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00,   //>!
    0x22, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //"
    0x23, 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00,   //#
    0x24, 0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30, 0x00,   //$
    0x25, 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00,   //%
    0x26, 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00,   //&
    0x27, 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,   //'
    0x28, 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00,   //(
    0x29, 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00,   //)
    0x2a, 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00,   //*
    0x2b, 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0x00,   //+
    0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60,   //,
    0x2d, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00,   //-
    0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00,   //.
    0x2f, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00,   //>/
    0x30, 0x7c, 0xc6, 0xce, 0xde, 0xf6, 0xe6, 0x7c, 0x00,   //0
    0x31, 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x00,   //1
    0x32, 0x78, 0xcc, 0x0c, 0x38, 0x60, 0xcc, 0xfc, 0x00,   //2
    0x33, 0x78, 0xcc, 0x0c, 0x38, 0x0c, 0xcc, 0x78, 0x00,   //3
    0x34, 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00,   //4
    0x35, 0xfc, 0xc0, 0xf8, 0x0c, 0x0c, 0xcc, 0x78, 0x00,   //5
    0x36, 0x38, 0x60, 0xc0, 0xf8, 0xcc, 0xcc, 0x78, 0x00,   //6
    0x37, 0xfc, 0xcc, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00,   //7
    0x38, 0x78, 0xcc, 0xcc, 0x78, 0xcc, 0xcc, 0x78, 0x00,   //8
    0x39, 0x78, 0xcc, 0xcc, 0x7c, 0x0c, 0x18, 0x70, 0x00,   //9
    0x3a, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00,   //:
    0x3b, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60,   //;
    0x3c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00,   //<
    0x3d, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00,   //=
    0x3e, 0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00,   //>
    0x3f, 0x78, 0xcc, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x00,   //?
    0x40, 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00,   //@
    0x41, 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00,   //A
    0x42, 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00,   //B
    0x43, 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00,   //C
    0x44, 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00,   //D
    0x45, 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00,   //E
    0x46, 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00,   //F
    0x47, 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00,   //G
    0x48, 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00,   //H
    0x49, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,   //I
    0x4a, 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00,   //J
    0x4b, 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00,   //K
    0x4c, 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00,   //L
    0x4d, 0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00,   //M
    0x4e, 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00,   //N
    0x4f, 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00,   //O
    0x50, 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00,   //P
    0x51, 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00,   //Q
    0x52, 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00,   //R
    0x53, 0x78, 0xcc, 0xe0, 0x70, 0x1c, 0xcc, 0x78, 0x00,   //S
    0x54, 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,   //T
    0x55, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x00,   //U
    0x56, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00,   //V
    0x57, 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00,   //W
    0x58, 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00,   //X
    0x59, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00,   //Y
    0x5a, 0xfe, 0xc6, 0x8c, 0x18, 0x32, 0x66, 0xfe, 0x00,   //Z
    0x5b, 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00,   //[
    0x5c, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00,   //\<
    0x5d, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00,   //]
    0x5e, 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00,   //^
    0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,   //_
    0x60, 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,   //`
    0x61, 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00,   //a
    0x62, 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0xdc, 0x00,   //b
    0x63, 0x00, 0x00, 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x00,   //c
    0x64, 0x1c, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0x76, 0x00,   //d
    0x65, 0x00, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00,   //e
    0x66, 0x38, 0x6c, 0x60, 0xf0, 0x60, 0x60, 0xf0, 0x00,   //f
    0x67, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8,   //g
    0x68, 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00,   //h
    0x69, 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,   //i
    0x6a, 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78,   //j
    0x6b, 0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00,   //k
    0x6c, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,   //l
    0x6d, 0x00, 0x00, 0xcc, 0xfe, 0xfe, 0xd6, 0xc6, 0x00,   //m
    0x6e, 0x00, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0x00,   //n
    0x6f, 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x00,   //o
    0x70, 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0,   //p
    0x71, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e,   //q
    0x72, 0x00, 0x00, 0xdc, 0x76, 0x66, 0x60, 0xf0, 0x00,   //r
    0x73, 0x00, 0x00, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x00,   //s
    0x74, 0x10, 0x30, 0x7c, 0x30, 0x30, 0x34, 0x18, 0x00,   //t
    0x75, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00,   //u
    0x76, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00,   //v
    0x77, 0x00, 0x00, 0xc6, 0xd6, 0xfe, 0xfe, 0x6c, 0x00,   //w
    0x78, 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00,   //x
    0x79, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8,   //y
    0x7a, 0x00, 0x00, 0xfc, 0x98, 0x30, 0x64, 0xfc, 0x00,   //z
    0x7b, 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c, 0x00,   //{
    0x7c, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,   //|
    0x7d, 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00,   //}
    0x7e, 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //~
};


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

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        vPrintString( "displayLED with freeRTOS y sAPI.\r\n" );
        vTaskDisplayLedTest(pvParameters);
        xSemaphoreGive(xMutexUART);
    }
   
    size_t      length=8*8; //8 columns per module, 8 modules per row
    //uint8_t     data_8b[length];
    uint8_t     data_8b[] = {
/*        
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00, 
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00, 
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00, 
        0x00, 0xFF, 0x0A, 0xA0, 0xAB, 0xBA, 0xFF, 0x00
*/      
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
  
        for (int j=0;  j< 16*2 ;j++){ // rows
        // 16 rows/panel, 2 panels per display

            // send_data 
            for (int i=0 ; i< length; i++){ // columns
            // row data length
                uint8_t str1[]="ab";
                uint8_t str1_len=strlen(str1);
                #define buffer_size str1_len*8
                uint8_t buffer[buffer_size];
                string_read_to_8x8_bytes_out(str1,str1_len, );
                data_8b[i] = buffer[j];

                for (int k=0 ; k< 8; k++){ 
                // k< 8 bits , 8 bits per module
                    gpioWrite(panel_1, (data_8b[i] >> k) & (0x01));
                    gpioWrite(panel_2, (data_8b[i] >> k) & (0x01));
                    gpioWrite(clk, ON);
                    gpioWrite(clk, OFF);
                }
            }
            // latch 
            gpioWrite(latch, ON);
            gpioWrite(latch, OFF);

            // deco scan 
            if((j%1)==0){ gpioToggle(deco_A0); }
            if((j%2)==0){ gpioToggle(deco_A1); }
            if((j%4)==0){ gpioToggle(deco_A2); }
            if((j%8)==0){ gpioToggle(deco_A3); }

            vTaskDelayUntil( &xLastWakeTimeDisplayLed, xFreq);
        }
    }
}
/*
*/

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


#define ascii_index 95
#define buffer_size str1_len*8
uint16_t i,j,k;

void vTaskDisplayLedTest( void *pvParameters ){

//uint8_t str1[]="Hi, how are you?";
uint8_t str1[]="ab";    
uint8_t str1_len=strlen(str1);
uint8_t buffer[buffer_size];
string_read_to_8x8_bytes_out(str1,str1_len,buffer);

for (i=0;i<str1_len;i++)
{
    printf("letter %c:\n", str1[i]);
    for (j=0;j<8;j++){
    printf("0x%.2x ", buffer[(i*8)+j]);
    if (j%8==7)printf("\n");}
}

}
/*
*/

void string_read_to_8x8_bytes_out(uint8_t *str_in, uint8_t strlen, uint8_t *array_out)
{
    for (i=0;i<strlen;i++)
    {
        for (k=0;k<ascii_index;k++)
        {
            if (str_in[i]==new_ascii[k*9])
            {
                for (j=0;j<8;j++)
                {
                    array_out[(i*8)+j]=new_ascii[((k*9)+1)+j];
                }
            }
        }
    }
}

void msgToData(uint8_t *str_in, uint8_t strlen, uint8_t *array_out){

    string_read_to_8x8_bytes_out(str_in,  strlen, array_out);

}

void dataToPanelRows(uint8_t *array_in, uint8_t array_len, uint8_t *panel_out){

/*
    uint16_t i,j,k;
    if(panel_len == array_len) // q < l
    {
        for( i=0; i<array_len; i++){
            panel_out[i]=array_in[i*8+k];
        }
    }

    else if (panel_len > array_len)
    {

    }
*/
}

void panelRowsToDisplayEncode(uint8_t *panel_in, uint8_t panel_len, uint8_t *display_out){
/*
dataOut >> k = dataIn >> k 
dataOut >> k+1 = dataIn >> k 
*/

}



uint8_t* f1(uint8_t x)
{
    uint8_t y=0x00;
    uint8_t z=0x00;
    uint8_t mask=0b11110000;
    y = x & mask;
    z = x & ~mask;
    uint8_t out[2] = {y,z};
    return out;
}

int hi_nibble(int x)
{
    int mask=0xF0;
    int y;
    y = x & mask;
    return y;
}

int low_nibble(int x){
    int mask=0xF0;
    int z;
    z = x & ~mask;
    return z;
}

int f(int y)
{
    int mask=0xF0;
    int yy=0x00;
    int n=7;
    int a=0x00;
    int b=0x00;
    for (int k=0; k<8; k++ ){
        a |= (y>>((n+1)/2))   & (mask>>k);
        b |= (y>>((n+1)/2-1)) & (mask>>k);
        yy = a | b;
    }
    return yy;
}

int g(int z)
{
    int mask=0x01;
    int zz=0x00;
    int n=7;
    int a=0x00;
    int b=0x00;
    for (int k=0; k<8; k++ ){
        a |= (z<<((n+1)/2))   & (mask<<k);
        b |= (z<<((n+1)/2-1)) & (mask<<k);
        zz = a | b;
    }
    return zz;
}

