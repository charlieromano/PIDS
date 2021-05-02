/**
 * @file userTasks.h
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

#include "AO.h"

/**
 * @brief Heart Beat Task
 * This task only blink green led to know the system is running.
 * @param taskParmPtr 
 */
void heartbeat_task(void *taskParmPtr);

void uart_task(void *taskParmPtr);

void tarea_auxiliar(void *taskParmPtr);

void uart_task_AO(void *taskParmPtr);

#endif /* __USER_TASKS_H__ */
