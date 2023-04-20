//statemachine_displayLed.c
#include "statemachine_displayLed.h"


uint8_t 	deco_counter;
extern gpioMap_t 	deco_A0;
extern gpioMap_t 	deco_A1;
extern gpioMap_t 	deco_A2;
extern gpioMap_t 	deco_A3;/*DECO_E3_E1*/
extern gpioMap_t 	clk;
extern gpioMap_t  	latch;



sStateMachine_displayLed fsmDisplayLed[] = 
{
	{STATE_DISPLAY_INIT, evDisplayInit, displayled_initHandler},
	{STATE_DISPLAY_IDLE, evDisplay_msg_received, displayled_idleHandler}
	{STATE_DISPLAY_ENCODING, evDisplay_ready, displayled_dataHandler},
	{STATE_DISPLAY_LATCH, evDisplay_ready, displayled_latchHandler},
	{STATE_DISPLAY_OUTPUT_ENABLE, evDisplay_ready, displayled_outputHandler},
	{STATE_DISPLAY_WAITING, evDisplay_timeout, displayled_dataHandler},
	{STATE_DISPLAY_IDLE, evDisplay_msg_received, displayled_dataHandler}

};

eSystemState_displayLed 	displayled_initHandler(void){

	deco_counter = 0;

	return STATE_DISPLAY_IDLE;
}

eSystemState_displayLed 	displayled_idleHandler(void){

     if(xQueueSend(queueHandle_button, &newEventFromTimer, 0U)!=pdPASS){
         perror("Error sending data to the queueHandle_button\r\n");
      }
 
    if( pdPASS == xQueueReceive(..., &..., portMAX_DELAY)){

    }


	return STATE_DISPLAY_ENCODING;

}

eSystemState_displayLed 	displayled_dataHandler(void){
	/* msg completed*/
	/*
	if(){
		return STATE_DISPLAY_IDLE;
	}*/
/*
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
*/
	return STATE_DISPLAY_LATCH;
}

eSystemState_displayLed 	displayled_latchHandler(void){

    // latch 
    gpioWrite(latch, ON);
    gpioWrite(latch, OFF);
    // next row
    deco_counter++;
    deco_counter%=DISPLAY_MAX_ROWS;

	return STATE_DISPLAY_OUTPUT_ENABLE;

}

eSystemState_displayLed 	displayled_outputHandler(void){

    // deco scan 
    if((deco_counter%1)==0){ gpioToggle(deco_A0); }
    if((deco_counter%2)==0){ gpioToggle(deco_A1); }
    if((deco_counter%4)==0){ gpioToggle(deco_A2); }
    if((deco_counter%8)==0){ gpioToggle(deco_A3); }

	return STATE_DISPLAY_WAITING;

}
