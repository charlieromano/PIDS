//statemachine_displayLed.c
#include "statemachine_displayLed.h"


uint8_t 	deco_counter;
extern gpioMap_t 	deco_A0;
extern gpioMap_t 	deco_A1;
extern gpioMap_t 	deco_A2;
extern gpioMap_t 	deco_A3;/*DECO_E3_E1*/


sStateMachine_displayLed fsmMachineDisplayLed [] = 
{
	{STATE_DISPLAY_INIT, evDisplayInit, displayled_initHandler},
	{STATE_DISPLAY_ENCODING, evDisplay_ready, displayled_dataHandler},
	{STATE_DISPLAY_LATCH, evDisplay_ready, displayled_latchHandler},
	{STATE_DISPLAY_OUTPUT_ENABLE, evDisplay_ready, displayled_outputHandler},
	{STATE_DISPLAY_WAITING, evDisplay_timeout, displayled_dataHandler},
	{STATE_DISPLAY_IDLE, evDisplay_msg_received, displayled_dataHandler}

};

eSystemState_displayLed 	displayled_initHandler(void){

	deco_counter = 0;

	return STATE_DISPLAY_ENCODING;
}

eSystemState_displayLed 	displayled_dataHandler(void){
	if(/* msg completed*/){
		return STATE_DISPLAY_IDLE;
	}
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
