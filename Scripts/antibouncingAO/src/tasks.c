//tasks.c
#include "tasks.h"

/*
void vTaskTA(void *xTimerHandle)
{
	(void)xTimerHandle;
	eSystemEvent newEvent;

	while(true){
		vPrintString("Task TA is running.\r\n");
		eSystemState nextState = STATE_INIT;
		newEvent=evInit;
		int i=0;

		while(i<6){
			xQueueReceive(queueHandle, &data, portMAX_DELAY);
			newEvent = data;
			fsmTest[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmTest[nextState].fsmHandler)();
			i++;
		}
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler);
	}
}
*/

void vTaskTB(void *xTimerHandle)
{
	(void)xTimerHandle;
	eSystemEvent_AB newEvent;

	while(true){
		vPrintString("Task TB is running.\r\n");
		eSystemState_AB nextState = STATE_INIT_AB;
		newEvent=evInit_AB;
		int i=0;

		while(i<8){
			xQueueReceive(queueHandle_AB, &data_AB, portMAX_DELAY);
			newEvent = data_AB;
			fsmMachineAB[nextState].fsmEvent == newEvent; //TO DO:data.event
			nextState = (*fsmMachineAB[nextState].fsmHandler)();
			i++;
		}
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler_AB);
	}
}
