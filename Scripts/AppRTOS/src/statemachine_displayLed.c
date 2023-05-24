//statemachine_displayLed.c
#include "statemachine_displayLed.h"

extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

extern uint8_t      display_deco_cnt;
extern gpioMap_t 	display_deco_A0;
extern gpioMap_t 	display_deco_A1;
extern gpioMap_t 	display_deco_A2;
extern gpioMap_t 	display_deco_A3;/*DECO_E3_E1*/
extern gpioMap_t 	display_clk;
extern gpioMap_t  	display_latch;
extern gpioMap_t    display_panel_1;

sStateMachine_displayLed fsmDisplayLed[] = 
{
    {STATE_DISPLAY_INIT, evDisplayInit, displayled_initHandler},
    {STATE_DISPLAY_IDLE, evDisplay_msg_received, displayled_idleHandler},
    {STATE_DISPLAY_PROCESSING, evDisplay_timeout, displayled_procHandler},
    {STATE_DISPLAY_ENCODING, evDisplay_timeout, displayled_dataHandler}
};

// Settings 
static  uint8_t     display_size = DISPLAY_ROWS*DISPLAY_COLS;
uint8_t             display_buffer[DISPLAY_ROWS*DISPLAY_COLS];
uint8_t             display_buffer_idx;
uint8_t             display_deco_cnt;
uint8_t             display_timer_cnt;

uint8_t global_index;

// Globals
static char             *msg_ptr = NULL;
extern bool_t  display_msg_flag;
extern const uint8_t buf_len;


eSystemState_displayLed 	displayled_initHandler(void){
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("STATE_DISPLAY_INIT\r\n");
      xSemaphoreGive(xMutexUART);
   }
/*
*/
    display_buffer_idx = 0;
	display_deco_cnt   = 0;
    display_msg_flag   = 0;
    display_timer_cnt  = 10;
     
	return STATE_DISPLAY_IDLE;
}

eSystemState_displayLed 	displayled_idleHandler(void){
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_DISPLAY_IDLE\r\n");
        xSemaphoreGive(xMutexUART);
    }

    if (display_msg_flag) {
        return STATE_DISPLAY_PROCESSING;
    }   
/*
*/
    return STATE_DISPLAY_IDLE;    
}
extern  uint8_t idx;

eSystemState_displayLed     displayled_procHandler(void){
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("STATE_DISPLAY_PROCESSING\r\n");
      xSemaphoreGive(xMutexUART);
   }

   char str1[idx];
    
    if(display_msg_flag==1){
        for(int i=0; i<idx;i++){
            str1[i]=msg_ptr[i];
        }
        vPortFree(msg_ptr);
        msg_ptr = NULL;

    uint8_t str1_len=strlen(str1);
    uint8_t buffer_size=str1_len*CHAR_LENGTH;
    uint8_t buffer[buffer_size];

/*
*/
    string_read_to_8x8_bytes_out(str1,str1_len,buffer);

    int n=CHAR_LENGTH; 
    int m=str1_len;
    int p=DISPLAY_ROWS;
    int q=DISPLAY_COLS;

    int display_size = p*q;

    uint8_t B[display_size];
    for(int i=0; i<display_size;i++)
    B[i]=0;

    reshape_to_display(buffer, display_buffer, buffer_size, display_size);

    }
    return STATE_DISPLAY_ENCODING;
}

/*
eSystemState_displayLed     displayled_procHandler(void){
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("STATE_DISPLAY_PROCESSING\r\n");
      xSemaphoreGive(xMutexUART);
   }

//    char *str1;
    char str1[]="Hola msg";
    uint8_t str1_len=strlen(str1);
    uint8_t buffer_size=str1_len*CHAR_LENGTH;
    uint8_t buffer[buffer_size];


    //strcpy(str1, msg_ptr);
    string_read_to_8x8_bytes_out(str1,str1_len,buffer);

    int n=CHAR_LENGTH; 
    int m=str1_len;
    int p=DISPLAY_ROWS;
    int q=DISPLAY_COLS;

    int display_size = p*q;

    uint8_t B[display_size];
    for(int i=0; i<display_size;i++)
    B[i]=0;

    reshape_to_display(buffer, display_buffer, buffer_size, display_size);

    return STATE_DISPLAY_ENCODING;
}
*/


eSystemState_displayLed     displayled_dataHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("STATE_DISPLAY_ENCODING\r\n");
      //printf("index: %d\r\n",display_buffer_idx);
      xSemaphoreGive(xMutexUART);
    }

    if (!display_msg_flag) {
        return STATE_DISPLAY_IDLE;
    }

    display_timer_cnt--;
    if(!display_timer_cnt){
        display_msg_flag=0;
    };    

    uint8_t data_8b;
    bool_t value;

    for(int i=0; i<display_size; i++){
        
        data_8b = display_buffer[i];
        
        for(int j=0; j<8; j++){
            
            // display_data 
            value = (((data_8b << j ) & 0x80 ) == 0) ? 0 : 1;
            printf("%d",value);
            gpioWrite(display_panel_1, value);
            
            // clock 
            gpioWrite(display_clk, ON);
            gpioWrite(display_clk, OFF);
        }
        
        if(i%DISPLAY_COLS==0){
            // display_latch 
            printf("\r\n");
            gpioWrite(display_latch, ON);
            gpioWrite(display_latch, OFF);
            
            // display_row_scanning
            display_deco_cnt++;
            display_deco_cnt%=DISPLAY_ROWS;
            if((display_deco_cnt%1)==0){ gpioToggle(display_deco_A0); }
            if((display_deco_cnt%2)==0){ gpioToggle(display_deco_A1); }
            if((display_deco_cnt%4)==0){ gpioToggle(display_deco_A2); }
            if((display_deco_cnt%8)==0){ gpioToggle(display_deco_A3); }
        }
    }
    
    return STATE_DISPLAY_ENCODING;
}
