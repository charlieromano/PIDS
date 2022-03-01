//statemachine.c
#include "statemachine_button.h"

extern gpioMap_t button;

eSystemState_button 	pushingUpHandler(void)
{ 
	printf("STATE DOWN\n");
	gpioWrite(LEDG, OFF);
	gpioWrite(LEDB, ON);
	if(gpioRead(button)==true){
		printf("Button pressed:\n");
		return STATE_BUTTON_RISING;
	}
	else{
		return STATE_BUTTON_DOWN;		
	}
}

eSystemState_button 	pushingDownHandler(void)
{ 
	printf("STATE UP\n");
	gpioWrite(LEDB, OFF);
	gpioWrite(LEDG, ON);
	if(gpioRead(button)!=true){
		printf("Button pressed:\n");
		return STATE_BUTTON_FALLING;
	}
	else{
		return STATE_BUTTON_UP;		
	}
}

eSystemState_button 	bouncingUpHandler(void)
{ 
	if(gpioRead(button)==true){
		printf("Button pressed..\n");
		return STATE_BUTTON_UP;
	}
	else{
	//evBouncing
		return STATE_BUTTON_DOWN; 
	}
}

eSystemState_button 	bouncingDownHandler(void)
{ 
	if(gpioRead(button)==true){
		printf("Button pressed..\n");
		return STATE_BUTTON_UP;
	}
	else{
	//evBouncing
		return STATE_BUTTON_DOWN; 
	}
}


sStateMachine_button fsmButton [] = 
{
	{STATE_BUTTON_DOWN, evPushed, pushingUpHandler},
	{STATE_BUTTON_UP, evPushed, pushingDownHandler},
	{STATE_BUTTON_FALLING, evBouncing, bouncingDownHandler},
	{STATE_BUTTON_RISING, evBouncing, bouncingUpHandler}
};
