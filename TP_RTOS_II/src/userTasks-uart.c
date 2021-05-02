/**
 * @file userTasks-uart.c
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "userTasks.h"
#include "semphr.h"

#define MSG_ERROR1 "Error 1 --"
#define MSG_ERROR2 "Error 2 --"
#define MSG_ERROR1_LENGTH (sizeof(MSG_ERROR1) - 1)
#define MSG_ERROR2_LENGTH (sizeof(MSG_ERROR2) - 1)
#define MSG_OPTION_POSITION 0

activeObjectParam_t params;

static void SendPackage(frame *uart, package *packageToSend);

/* Used in V1.0 witout active object */

//***********************************************************************
/*                    Used in V1.0 witout active object                */
//***********************************************************************
void uart_task(void *taskParmPtr)
{
    frame *uart = (frame *)taskParmPtr;
    package *packageToProcess;
    char option;

    while (TRUE)
    {
        gpioToggle(LED1);

        /* Only go forward if receive a new package */
        xQueueReceive(uart->QueueRxPkg, &packageToProcess, portMAX_DELAY);
        /* Peek option character from package */
        option = packageToProcess->msg[MSG_OPTION_POSITION];

        switch (option)
        {
        case 'm':
            if (message_lowercase(packageToProcess->msg, packageToProcess->msg_l - CRC_LENGTH) == false)
            {
                /* If lowercase process fail, clear package and add MSG_ERROR1 */
                package_clear(packageToProcess);
                package_addString(packageToProcess, MSG_ERROR1, MSG_ERROR1_LENGTH);
            }
            break;
        case 'M':
            if (message_uppercase(packageToProcess->msg, packageToProcess->msg_l - CRC_LENGTH) == false)
            {
                /* If lowercase process fail, clear package and add MSG_ERROR1 */
                package_clear(packageToProcess);
                package_addString(packageToProcess, MSG_ERROR1, MSG_ERROR1_LENGTH);
            }
            break;
        default:
            /* If command is not list, clear package and add MSG_ERROR2 */
            package_clear(packageToProcess);
            package_addString(packageToProcess, MSG_ERROR2, MSG_ERROR2_LENGTH);
            break;
        }
        /* Calculate new CRC from modified package and send it */
        package_calc(packageToProcess);
        SendPackage(uart, packageToProcess);
    }
}

//***********************************************************************
/*                  Used in V2.0 with active object                    */
//***********************************************************************
void tarea_auxiliar(void *taskParmPtr)
{
    frame *uart = (frame *)taskParmPtr;

    activeObjectParam_t auxResponse;

    while (TRUE)
    {
        if (xQueueReceive(params.colaCapa3, &auxResponse, portMAX_DELAY))
        {
            /* Calculate new CRC from modified package and send it */
            package_calc(auxResponse.packageToProcess);
            SendPackage(uart, auxResponse.packageToProcess);
        }
    }
}

void uart_task_AO(void *taskParmPtr)
{
    frame *uart = (frame *)taskParmPtr;
    package *packageToProcess;
    char option;

    activeObject_t lowercaseAO;
    lowercaseAO.itIsAlive = FALSE;

    activeObject_t uppercaseAO;
    uppercaseAO.itIsAlive = FALSE;

    while (TRUE)
    {
        gpioToggle(LED1);

        /* Only go forward if receive a new package */
        xQueueReceive(uart->QueueRxPkg, &packageToProcess, portMAX_DELAY);
        /* Peek option character from package */
        option = packageToProcess->msg[MSG_OPTION_POSITION];

        switch (option)
        {
        case 'm':
            if (lowercaseAO.itIsAlive == FALSE)
            {
                params.packageToProcess = packageToProcess;
                // Se crea el objeto activo, con el comando correspondiente y tarea asociada.
                activeObjectCreate(&lowercaseAO, message_lowercase_AO, activeObjectTask);
            }

            // Y enviamos el dato a la cola para procesar.
            activeObjectEnqueue(&lowercaseAO, &params);
            break;
        case 'M':
            if (uppercaseAO.itIsAlive == FALSE)
            {
                params.packageToProcess = packageToProcess;
                // Se crea el objeto activo, con el comando correspondiente y tarea asociada.
                activeObjectCreate(&uppercaseAO, message_uppercase_AO, activeObjectTask);
            }

            // Y enviamos el dato a la cola para procesar.
            activeObjectEnqueue(&uppercaseAO, &params);

            break;
        default:
            /* If command is not list, clear package and add MSG_ERROR2 */
            package_clear(packageToProcess);
            package_addString(packageToProcess, MSG_ERROR2, MSG_ERROR2_LENGTH);
            package_calc(packageToProcess);
            SendPackage(uart, packageToProcess);
            break;
        }
    }
}
//********************************************************************************************************************

static void SendPackage(frame *uart, package *packageToSend)
{
    /* Send memory direction of package to queue */
    xQueueSend(uart->QueueTxPkg, &packageToSend, PROTOCOL_TIMEOUT);

    if (xTimerIsTimerActive(uart->onTxTimeOut) == pdFALSE)
    {
        /* xTimer is not active, start it. */
        onTxTimeOutCallback(uart->onTxTimeOut);
    }
}
