//statemachine.c
#include "statemachine_button.h"

sStateMachine_button fsmButton [] = 
{
	{STATE_BUTTON_INIT, evInit, buttonInitHandler},
	{STATE_BUTTON_UP, evPushed, buttonPushedDownHandler},
	{STATE_BUTTON_FALLING, evButtonTimeout, bouncingDownHandler},
	{STATE_BUTTON_DOWN, evPushed, buttonPushedUpHandler},
	{STATE_BUTTON_RISING, evButtonTimeout, bouncingUpHandler},
};

eSystemState_button 	buttonInitHandler(void)
{
	if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      	printf("button init...UP;\n");
      	xSemaphoreGive(xMutexUART);
    }
    timer_cnt=0;
    timer_flag=false;
	return STATE_BUTTON_UP;
}

eSystemState_button 	buttonPushedDownHandler(void)
{
	timer_flag=true;
	return STATE_BUTTON_FALLING;
}

eSystemState_button 	bouncingDownHandler(void)
{
	/* GPIO: VCC=true, GND=false, default=true */ 
	if((gpioRead(button)==false)
		&&(timer_cnt>TIMER_MIN_TIMEOUT)){

		timer_flag=false;
		printf("DOWN\r\n");
		return STATE_BUTTON_DOWN;
	}

	else if((gpioRead(button)==true)
		&&(timer_cnt>TIMER_MIN_TIMEOUT)){

		timer_flag=false;
		printf("UP\r\n");
		return STATE_BUTTON_UP;
	}
	
	return STATE_BUTTON_FALLING;
}

eSystemState_button 	buttonPushedUpHandler(void)
{
	timer_flag=true;
	return STATE_BUTTON_RISING;
}


eSystemState_button 	bouncingUpHandler(void)
{
	/* GPIO: VCC=true, GND=false, default=true */ 
	if((gpioRead(button)==false)
		&&(timer_cnt>TIMER_MIN_TIMEOUT)){

		timer_flag=false;
		printf("UP\r\n");
		return STATE_BUTTON_UP;
	}

	else if((gpioRead(button)==true)
		&&(timer_cnt>TIMER_MIN_TIMEOUT)){
	
		timer_flag=false;
		printf("DOWN\r\n");
		return STATE_BUTTON_DOWN;
	}
	
	return STATE_BUTTON_RISING;

}
