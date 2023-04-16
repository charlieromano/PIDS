//statemachine_displayLed.c
#include "statemachine_displayLed.h"


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

	return STATE_DISPLAY_ENCODING;
}

eSystemState_displayLed 	displayled_dataHandler(void){
	if(/* msg completed*/){
		return STATE_DISPLAY_IDLE;
	}
	return STATE_DISPLAY_LATCH;
}

eSystemState_displayLed 	displayled_latchHandler(void){

	return STATE_DISPLAY_OUTPUT_ENABLE;

}

eSystemState_displayLed 	displayled_outputHandler(void){

	return STATE_DISPLAY_WAITING;

}

