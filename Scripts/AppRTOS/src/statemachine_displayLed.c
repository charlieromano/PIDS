//statemachine_displayLed.c
#include "statemachine_displayLed.h"

sStateMachine_displayLed fsmDisplayLed[] = 
{
    {STATE_DISPLAYLED_INIT, evDisplayled_init, displayled_initHandler},
    {STATE_DISPLAYLED_IDLE, evDisplayled_msg_received, displayled_idleHandler},
    {STATE_DISPLAYLED_PROCESSING, evDisplayled_timeout, displayled_procHandler},
    {STATE_DISPLAYLED_ENCODING, evDisplayled_timeout, displayled_dataHandler}
};

// Globals
extern char *messages[];

extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

extern uint8_t      displayled_deco_cnt;
extern gpioMap_t 	displayled_deco_A0;
extern gpioMap_t 	displayled_deco_A1;
extern gpioMap_t 	displayled_deco_A2;
extern gpioMap_t 	displayled_deco_A3;
extern gpioMap_t 	displayled_clk;
extern gpioMap_t  	displayled_latch;
extern gpioMap_t    displayled_panel_1;
extern gpioMap_t    displayled_panel_2;

bool_t      displayled_msg_flag;

uint8_t     displayled_size = DISPLAYLED_ROWS*DISPLAYLED_COLS;
uint8_t     displayled_buffer[DISPLAYLED_ROWS*DISPLAYLED_COLS];
uint8_t     displayled_buffer_idx;
uint8_t     displayled_deco_cnt;
uint8_t     displayled_timer_cnt;
uint8_t     displayled_msg_idx;

eSystemState_displayLed 	displayled_initHandler(void){
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      //printf("STATE_DISPLAYLED_INIT\r\n");
      xSemaphoreGive(xMutexUART);
   }
/*
*/
    displayled_buffer_idx = 0;
	displayled_deco_cnt   = 0;
    displayled_msg_flag   = 0;
    displayled_msg_idx    = 0;
     
	return STATE_DISPLAYLED_IDLE;
}

eSystemState_displayLed 	displayled_idleHandler(void){
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_DISPLAYLED_IDLE\r\n");
        xSemaphoreGive(xMutexUART);
    }

    displayled_timer_cnt  = MESSAGES_FLICKR_NUMBER;

    if (displayled_msg_flag) {
        return STATE_DISPLAYLED_PROCESSING;
    }   
/*
*/
    return STATE_DISPLAYLED_IDLE;    
}

eSystemState_displayLed     displayled_procHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      //printf("STATE_DISPLAYLED_PROCESSING\r\n");
      xSemaphoreGive(xMutexUART);
   }
/*
*/
    char *str1=messages[displayled_msg_idx];

    uint8_t str1_len=strlen(str1);
    uint8_t buffer_size=str1_len*CHAR_LENGTH;
    uint8_t buffer[buffer_size];

    string_read_to_8x8_bytes_out(str1,str1_len,buffer);

    int n=CHAR_LENGTH; 
    int m=str1_len;
    int p=DISPLAYLED_ROWS;
    int q=DISPLAYLED_COLS;

    int displayled_size = p*q;

    uint8_t B[displayled_size];
    for(int i=0; i<displayled_size;i++)
    B[i]=0;

    reshape_to_display(buffer, displayled_buffer, buffer_size, displayled_size);

    displayled_msg_idx++;
    displayled_msg_idx%=MESSAGES_TOTAL_NUMBER;
    displayled_msg_flag=0;

    return STATE_DISPLAYLED_ENCODING;
}

eSystemState_displayLed     displayled_dataHandler(void){

    uint8_t data_8b;
    bool_t  value;

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      //printf("STATE_DISPLAYLED_ENCODING\r\n");
      //printf("index: %d\r\n",displayled_buffer_idx);
      xSemaphoreGive(xMutexUART);
    }

    displayled_timer_cnt--;
    if(!displayled_timer_cnt){
        displayled_msg_flag=0;
        return STATE_DISPLAYLED_IDLE;
    };    

    for(int i=0; i<displayled_size; i++){
        
        data_8b = displayled_buffer[i];
        
        for(int j=0; j<8; j++){
            
            // displayled_data 
            value = (((data_8b << j ) & 0x80 ) == 0) ? 1 : 0;
            //printf("%d",value);
            gpioWrite(displayled_panel_1, value);
            gpioWrite(displayled_panel_2, value);
            
            // displayled_clock 
            gpioWrite(displayled_clk, ON);
            gpioWrite(displayled_clk, OFF);
        }
        
        if(i%DISPLAYLED_COLS==0){

            // displayled_latch 
            //printf("\r\n");
            gpioWrite(displayled_latch, ON);
            gpioWrite(displayled_latch, OFF);
            
            // displayled_row_scanning
            displayled_deco_cnt++;
            displayled_deco_cnt%=DISPLAYLED_ROWS;
            if((displayled_deco_cnt%1)==0){ gpioToggle(displayled_deco_A0); }
            if((displayled_deco_cnt%2)==0){ gpioToggle(displayled_deco_A1); }
            if((displayled_deco_cnt%4)==0){ gpioToggle(displayled_deco_A2); }
            if((displayled_deco_cnt%8)==0){ gpioToggle(displayled_deco_A3); }
        }
    }
    
    return STATE_DISPLAYLED_ENCODING;
}
