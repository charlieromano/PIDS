/*=============================================================================
 * Copyright (c) 2020, Luciano Francisco Vittori <lucianovittori99@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/07/13
 * Version: 1.0
 *===========================================================================*/

#ifndef PROGRAMS_TP_RTOS_II_INC_FRAME_DRIVER_H_
#define PROGRAMS_TP_RTOS_II_INC_FRAME_DRIVER_H_

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "sapi.h"
#include "package.h"
#include "message.h"
#include "ReceiveState.h"
#include "qmpool.h"

#define PROTOCOL_TIMEOUT pdMS_TO_TICKS(50)
#define UART_BUFFER_TX 50
#define UART_BUFFER_RX 50
#define UART_BUFFER (UART_BUFFER_TX + UART_BUFFER_RX)
#define POOL_BLOCK_SIZE sizeof(package)
#define POOL_SIZE (UART_BUFFER * POOL_BLOCK_SIZE)

/**
 * @brief frame driver
 * 
 */
typedef struct
{
    uartMap_t uartValue;
    uint32_t baudRate;
    char som;
    char eom;
    TimerHandle_t onTxTimeOut;
    TimerHandle_t onRxTimeOut;
    bool TransmissionAvailable;
    package *rxPkg;
    package *txPkg;
    QMPool memory;
    ReceiveStatePtr receiveState;
    QueueHandle_t QueueRxPkg;
    QueueHandle_t QueueTxPkg;
    SemaphoreHandle_t mutex;
    BaseType_t xHigherPriorityTaskWokenTx;
    BaseType_t xHigherPriorityTaskWokenRx;
} frame;

/**
 * @brief This function initate frame driver.
 * 
 * @param uart 
 * @param uart_selected 
 * @param baudrate 
 * @param SOM 
 * @param EOM 
 * @return true Object created
 * @return false error.
 */
bool Frame_Init(frame *uart, uartMap_t uart_selected, uint32_t baudrate, char SOM, char EOM);

/**
 * @brief Reception callback interrupt.
 * This is for hardware callback in transmission for selected UART.
 * @param ParmPtr
 */
void onRxCallback(void *ParmPtr);

/**
 * @brief Transmission callback interrupt.
 * This is for hardware callback in transmission for selected UART.
 * @param ParmPtr 
 */
void onTxCallback(void *ParmPtr);

/**
 * @brief General callback function for Tx timeout frame library.
 * 
 * @param pxTimer 
 */
void onTxTimeOutCallback(xTimerHandle pxTimer);

/**
 * @brief General callback function for Rx timeout frame library.
 * 
 * @param pxTimer 
 */
void onRxTimeOutCallback(xTimerHandle pxTimer);

/**
 * @brief Enable transmission interrupt.
 * 
 * @param uart 
 */
void txInterruptEnable(frame *uart);

/**
 * @brief Enable transmission interrupt.
 * 
 * @param uart 
 */
void rxInterruptEnable(frame *uart);

/**
 * @brief Disable transmission interrupt.
 * 
 * @param uart 
 */
void txInterruptDisable(frame *uart);

#endif /* PROGRAMS_TP_RTOS_II_INC_FRAME_DRIVER_H_ */
