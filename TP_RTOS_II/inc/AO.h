/*=============================================================================
 * Copyright (c) 2020, David Broin <davidmbroin@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/08/13
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _AO_H_
#define _AO_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "frame_driver.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

    /*=====[Definition macros of public constants]===============================*/

    /*=====[Public function-like macros]=========================================*/

    /*=====[Definitions of public data types]===============b=====================*/

    typedef struct
    {
        package *packageToProcess;
        QueueHandle_t colaCapa3;
    } activeObjectParam_t;

    typedef void (*callBackActObj_t)(activeObjectParam_t *);

    typedef struct
    {
        TaskFunction_t taskName;
        QueueHandle_t activeObjectQueue;
        callBackActObj_t callbackFunc;
        bool_t itIsAlive;
    } activeObject_t;

    /*=====[Prototypes (declarations) of public functions]=======================*/

    bool_t activeObjectCreate(activeObject_t *ao, callBackActObj_t callback, TaskFunction_t taskForAO);

    void activeObjectTask(void *pvParameters);

    void activeObjectEnqueue(activeObject_t *ao, activeObjectParam_t *value);

    void message_lowercase_AO(activeObjectParam_t *param);

    void message_uppercase_AO(activeObjectParam_t *param);

    /*=====[Prototypes (declarations) of public interrupt functions]=============*/

    /*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _AO_H_ */
