/*=============================================================================
 * Copyright (c) 2020, David Broin <davidmbroin@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/07/05
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "TP_RTOS_II.h"

/*=====[Inclusions of private function dependencies]=========================*/
#include "userTasks.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
frame uart;

activeObjectParam_t params;

int main(void)
{
	boardInit();

	if (Frame_Init(&uart, UART_USB, 115200, '(', ')') == false)
	{
		gpioWrite(LED2, ON);
		while (1)
			; // Task could not created
	}

	if (xTaskCreate(
			uart_task_AO,				  // Task Function
			(const char *)"uart_task_AO", // Task name, only for debug purpose.
			configMINIMAL_STACK_SIZE * 2, // Task stack.
			(void *)&uart,				  // Task parameters.
			tskIDLE_PRIORITY + 2,		  // Task priority.
			0							  // Task handle.
			) == pdFAIL)
	{
		gpioWrite(LED2, ON);
		while (1)
			; // Task could not created
	}

	if (xTaskCreate(
			tarea_auxiliar,					// Task Function
			(const char *)"tarea_auxiliar", // Task name, only for debug purpose.
			configMINIMAL_STACK_SIZE * 2,	// Task stack.
			(void *)&uart,					// Task parameters.
			tskIDLE_PRIORITY + 2,			// Task priority.
			0								// Task handle.
			) == pdFAIL)
	{
		gpioWrite(LED2, ON);
		while (1)
			; // Task could not created
	}

	if (xTaskCreate(
			heartbeat_task,				  // Task Function
			(const char *)"heart-beat",	  // Task name, only for debug purpose.
			configMINIMAL_STACK_SIZE / 2, // Task stack.
			0,							  // Task parameters.
			tskIDLE_PRIORITY + 1,		  // Task priority.
			0							  // Task handle.
			) == pdFAIL)
	{
		gpioWrite(LED2, ON);
		while (1)
			; // Task could not created
	}

	/* Queue create */
	params.colaCapa3 = xQueueCreate(UART_BUFFER, sizeof(activeObjectParam_t));
	if (params.colaCapa3 == pdFAIL)
	{
		gpioWrite(LED2, ON);
		while (1)
			; // Queue could not created
	}

	/* Initialize scheduler */
	vTaskStartScheduler();

	while (true)
		; /* If reach here it means that the scheduler could not start */

	/* YOU NEVER REACH HERE, because this program runs directly or on a
	micro-controller and is not called by any Operating System, as in the
	case of a PC program. */
	return 0;
}
