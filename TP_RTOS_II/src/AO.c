/*=====AO===========================================================
 
/*=============================================================================
 * Copyright (c) 2020, David Broin <davidmbroin@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/08/13
 *===========================================================================*/

#include "AO.h"

#define MSG_ERROR1 "Error 1 --"
#define MSG_ERROR2 "Error 2 --"
#define MSG_ERROR1_LENGTH (sizeof(MSG_ERROR1) - 1)
#define MSG_ERROR2_LENGTH (sizeof(MSG_ERROR2) - 1)

bool_t activeObjectCreate(activeObject_t *ao, callBackActObj_t callback, TaskFunction_t taskForAO)
{
    // Una variable local para saber si hemos creado correctamente los objetos.
    BaseType_t retValue = pdFALSE;

    // Creamos la cola asociada a este objeto activo.
    ao->activeObjectQueue = xQueueCreate(10, sizeof(activeObjectParam_t));

    // Asignamos la tarea al objeto activo.
    ao->taskName = taskForAO;

    // Si la cola se cre� sin inconvenientes.
    if (ao->activeObjectQueue != NULL)
    {
        // Asignamos el callback al objeto activo.
        ao->callbackFunc = callback;

        // Creamos la tarea asociada al objeto activo. A la tarea se le pasar� el objeto activo como par�metro.
        retValue = xTaskCreate(ao->taskName, (const char *)"Task For AO", configMINIMAL_STACK_SIZE * 2, ao, tskIDLE_PRIORITY + 2, NULL);
    }

    // Chequeamos si la tarea se cre� correctamente o no.
    if (retValue == pdPASS)
    {
        // Cargamos en la variable de estado del objeto activo el valor "true" para indicar que se ha creado.
        ao->itIsAlive = TRUE;

        // Devolvemos "true" para saber que el objeto activo se instanci� correctamente.
        return (TRUE);
    }
    else
    {
        // Caso contrario, devolvemos "false".
        return (FALSE);
    }
}

void activeObjectTask(void *pvParameters)
{
    // Una variable local para almacenar el dato desde la cola.
    activeObjectParam_t auxValue;

    // Obtenemos el puntero al objeto activo.
    activeObject_t *actObj = (activeObject_t *)pvParameters;

    // Cuando hay un evento, lo procesamos.
    while (1)
    {
        // Verifico si hay elementos para procesar en la cola. Si los hay, los proceso.
        if (uxQueueMessagesWaiting(actObj->activeObjectQueue))
        {
            xQueueReceive(actObj->activeObjectQueue, &auxValue, portMAX_DELAY);
            (actObj->callbackFunc)(&auxValue);
        }

        // Caso contrario, la cola est� vac�a, lo que significa que debo eliminar la tarea.
        else
        {
            // Cambiamos el estado de la variable de estado, para indicar que el objeto activo no existe m�s.
            actObj->itIsAlive = FALSE;

            // Borramos la cola del objeto activo.
            vQueueDelete(actObj->activeObjectQueue);

            // Y finalmente tenemos que eliminar la tarea asociada (suicidio).
            vTaskDelete(NULL);
        }
    }
}

void activeObjectEnqueue(activeObject_t *ao, activeObjectParam_t *value)
{
    // Y lo enviamos a la cola.
    xQueueSend(ao->activeObjectQueue, value, PROTOCOL_TIMEOUT);
}

void message_uppercase_AO(activeObjectParam_t *param)
{
    char *msg = param->packageToProcess->msg;
    uint8_t msg_l = param->packageToProcess->msg_l;
    if (message_uppercase(msg, msg_l - CRC_LENGTH) == false)
    {
        /* If lowercase process fail, clear package and add MSG_ERROR1 */
        package_clear(param->packageToProcess);
        package_addString(param->packageToProcess, MSG_ERROR1, MSG_ERROR1_LENGTH);
    }
    xQueueSend(param->colaCapa3, param, PROTOCOL_TIMEOUT);
}

void message_lowercase_AO(activeObjectParam_t *param)
{
    char *msg = param->packageToProcess->msg;
    uint8_t msg_l = param->packageToProcess->msg_l;
    if (message_lowercase(msg, msg_l - CRC_LENGTH) == false)
    {
        /* If lowercase process fail, clear package and add MSG_ERROR1 */
        package_clear(param->packageToProcess);
        package_addString(param->packageToProcess, MSG_ERROR1, MSG_ERROR1_LENGTH);
    }
    xQueueSend(param->colaCapa3, param, PROTOCOL_TIMEOUT);
}
