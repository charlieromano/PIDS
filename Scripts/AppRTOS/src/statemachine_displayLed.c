//statemachine_displayLed.c
#include "statemachine_displayLed.h"


uint8_t 	display_deco_cnt;
extern gpioMap_t 	deco_A0;
extern gpioMap_t 	deco_A1;
extern gpioMap_t 	deco_A2;
extern gpioMap_t 	deco_A3;/*DECO_E3_E1*/
extern gpioMap_t 	clk;
extern gpioMap_t  	latch;
extern gpioMap_t    panel_1;
extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

sStateMachine_displayLed fsmDisplayLed[] = 
{
	{STATE_DISPLAY_INIT, evDisplayInit, displayled_initHandler},
    {STATE_DISPLAY_IDLE, evDisplay_msg_received, displayled_idleHandler},
    {STATE_DISPLAY_PROCESSING, evDisplay_ready, displayled_procHandler},
	{STATE_DISPLAY_ENCODING, evDisplay_ready, displayled_dataHandler},
	{STATE_DISPLAY_LATCH, evDisplay_ready, displayled_latchHandler},
	{STATE_DISPLAY_OUTPUT_ENABLE,  evDisplay_timeout, displayled_outputHandler}
};


// Settings 
static  uint8_t      display_size = DISPLAY_ROWS*DISPLAY_COLS;
uint8_t      display_buffer[DISPLAY_ROWS*DISPLAY_COLS];
uint8_t      display_buffer_idx;
uint8_t      display_deco_cnt;

// Globals
static char             *msg_ptr = NULL;
static volatile uint8_t  msg_flag = 0;


eSystemState_displayLed 	displayled_initHandler(void){
/*
*/
    extern uint8_t buf_idx;
    extern uint8_t display_buffer[];
    extern uint8_t display_buffer_idx;
    extern uint8_t display_deco_cnt;

    buf_idx            = 0;
    display_buffer_idx = 0;
	display_deco_cnt   = 0;

    // Clear whole buffer
    memset(display_buffer, 0, display_size);
  
	return STATE_DISPLAY_IDLE;
}

eSystemState_displayLed 	displayled_idleHandler(void){
/*
*/
    if (msg_flag == 1) {

        vPortFree(msg_ptr);
        msg_ptr = NULL;
        msg_flag = 0;

        return STATE_DISPLAY_PROCESSING;
    }
}

eSystemState_displayLed 	displayled_procHandler(void){

    char *str1;
    strcpy(str1, msg_ptr);
    uint8_t str1_len=strlen(str1);
    uint8_t buffer_size=str1_len*CHAR_LENGTH;
    uint8_t buffer[buffer_size];

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

    display_buffer_idx=0;

	return STATE_DISPLAY_ENCODING;
}

eSystemState_displayLed     displayled_dataHandler(void){

    if(display_buffer_idx==display_size-1){
        display_buffer_idx=0;
        return STATE_DISPLAY_IDLE;
    }

    for(int i=0; i<DISPLAY_COLS ; i++){
        
        // one row encoding
        display_buffer_idx=display_deco_cnt*DISPLAY_COLS;
        uint8_t data_8b = display_buffer[display_buffer_idx+i];

        for (int k=0 ; k< 8; k++){ 
        // k: 8 bits per module
            gpioWrite(panel_1, (data_8b >> k) & (0x01));
            //gpioWrite(panel_2, (data_8b[i] >> k) & (0x01));
            gpioWrite(clk, ON);
            gpioWrite(clk, OFF);
        }        
    }    

    // latch 
    gpioWrite(latch, ON);
    gpioWrite(latch, OFF);

    return STATE_DISPLAY_OUTPUT_ENABLE;    
}


eSystemState_displayLed 	displayled_outputHandler(void){

    // deco scan 
    if((display_deco_cnt%1)==0){ gpioToggle(deco_A0); }
    if((display_deco_cnt%2)==0){ gpioToggle(deco_A1); }
    if((display_deco_cnt%4)==0){ gpioToggle(deco_A2); }
    if((display_deco_cnt%8)==0){ gpioToggle(deco_A3); }

    // next row
    display_deco_cnt++;
    display_deco_cnt%=DISPLAY_ROWS;

    //waiting
    //

	return STATE_DISPLAY_ENCODING;
}
