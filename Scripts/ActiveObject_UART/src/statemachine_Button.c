//statemachine.c
#include "statemachine_Button.h"

extern gpioMap_t button;

eSystemState_button 	buttonInitHandler(void){
	/* This button state machine starts with STATE UP */
	return STATE_BUTTON_UP;
}

eSystemState_button pushDownHandler(void)
{   /* STATE UP */
	if(gpioRead(button)==true){
		timer_flg=true;
		return STATE_BUTTON_FALLING;
	}else{
		return STATE_BUTTON_UP;		
	}
}

eSystemState_button bouncingDownHandler(void)
{   /* STATE FALLING */
   cnt = timer_cnt;
   if (timer_cnt==cnt++){
   		if(gpioRead(button)==true){
		return STATE_BUTTON_DOWN;
		}else{
		return STATE_BUTTON_UP; 
	}
}

eSystemState_button pushUpHandler(void)
{ 
	if(gpioRead(button)==true){
		return STATE_BUTTON_RISING;
	}else{
		return STATE_BUTTON_DOWN;		
	}
}


eSystemState_button bouncingUpHandler(void)
{ 
	if(gpioRead(button)==true){
		return STATE_BUTTON_UP;
	}else{
	//evBouncing
		return STATE_BUTTON_DOWN; 
	}
}


sStateMachine_button fsmButton [] = 
{
	{STATE_BUTTON_INIT, evInit, buttonInitHandler},
	{STATE_BUTTON_UP, evPushed, pushDownHandler},
	{STATE_BUTTON_FALLING, evPushed, bouncingUpHandler},
	{STATE_BUTTON_DOWN, evPushed, pushUpHandler},
	{STATE_BUTTON_RISING, evPushed, bouncingDownHandler}
};
