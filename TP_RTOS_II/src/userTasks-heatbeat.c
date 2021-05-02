/**
 * @file userTasks-heatbeat.c
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "userTasks.h"

#define HEARTBEAT_TICKS pdMS_TO_TICKS(500)

void heartbeat_task(void *taskParmPtr)
{
    /* Periodic task every HEARTBEAT_TICKS */
    portTickType xPeriodicity = HEARTBEAT_TICKS;
    portTickType xLastWakeTime = xTaskGetTickCount();

    while (TRUE)
    {
        gpioToggle(LED3);
        vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
    }
}
