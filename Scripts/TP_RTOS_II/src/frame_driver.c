/**
 * @file frame_driver.c
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "frame_driver.h"

package *poolMemory = NULL;

/**
 * @brief Wait start of frame state.
 * 
 * @param object 
 * @param receivedChar 
 */
static void waitForSOMAction(void *object, uint8_t receivedChar);

/**
 * @brief Store characters state.
 * 
 * @param object 
 * @param receivedChar 
 */
static void storeCharAction(void *object, uint8_t receivedChar);

bool Frame_Init(frame *uart, uartMap_t uart_selected, uint32_t baudrate, char som, char eom)
{
	if (NULL == uart)
	{
		return false;
	}

	/* Only do once if library did not initiated before */
	if (NULL == poolMemory)
	{
		/* Memory reserve to be used for the library */
		poolMemory = malloc(POOL_SIZE);
		if (NULL == poolMemory)
		{
			/* No memory available */
			return false;
		}
	}
	/* Map reserved memory to QMPool library */
	QMPool_init(&uart->memory, (void *)poolMemory, POOL_SIZE, POOL_BLOCK_SIZE);
	uart->uartValue = uart_selected;
	uart->baudRate = baudrate;
	uart->som = som;
	uart->eom = eom;
	uart->TransmissionAvailable = true;
	uart->QueueRxPkg = xQueueCreate(UART_BUFFER_RX, sizeof(uart->rxPkg));
	uart->QueueTxPkg = xQueueCreate(UART_BUFFER_TX, sizeof(uart->rxPkg));
	uart->mutex = xSemaphoreCreateMutex();
	uart->receiveState = createReceiveState("ReceiveState", waitForSOMAction);
	uart->onRxTimeOut = xTimerCreate("onRxTimeOut", PROTOCOL_TIMEOUT, pdFALSE, (void *)uart, onRxTimeOutCallback);
	uart->onTxTimeOut = xTimerCreate("onTxTimeOut", PROTOCOL_TIMEOUT, pdFALSE, (void *)uart, onTxTimeOutCallback);

	if ((pdFAIL == uart->QueueRxPkg) || (pdFAIL == uart->QueueTxPkg) || (pdFAIL == uart->mutex) || (pdFAIL == uart->onRxTimeOut) || (pdFAIL == uart->onTxTimeOut))
	{
		/* Objects could not created */
		return false;
	}
	else
	{
		/* Uart driver and interrupt initialization */
		uartConfig(uart->uartValue, uart->baudRate);
		rxInterruptEnable(uart);
		uartInterrupt(uart->uartValue, true);
		return true;
	}
}

void rxInterruptEnable(frame *uart)
{
	uartCallbackSet(uart->uartValue, UART_RECEIVE, onRxCallback, (void *)uart);
}

void txInterruptEnable(frame *uart)
{
	uartCallbackSet(uart->uartValue, UART_TRANSMITER_FREE, onTxCallback, (void *)uart);
}

void txInterruptDisable(frame *uart)
{
	uartCallbackClr(uart->uartValue, UART_TRANSMITER_FREE); // Deshabilito la interrupcion de Tx
}
/*=====[Implementations of interrupt functions]==============================*/

/* Global reception interrupt callback */
void onRxCallback(void *ParmPtr)
{
 	frame *uart = ParmPtr;
	uart->xHigherPriorityTaskWokenRx = pdFALSE;
	char charReceived;

	/* Open critical section */
	xSemaphoreTakeFromISR(uart->mutex, &uart->xHigherPriorityTaskWokenRx);
	charReceived = uartRxRead(uart->uartValue);
	uart->receiveState->execute(uart, charReceived);
	xSemaphoreGiveFromISR(uart->mutex, &uart->xHigherPriorityTaskWokenRx);
	/* Close critical section */

	/* Call scheduler if is nessesary */
	portYIELD_FROM_ISR(uart->xHigherPriorityTaskWokenRx);
}

/* Global transmission interrupt callback */
void onTxCallback(void *ParmPtr)
{
	frame *uart = ParmPtr;
	uart->xHigherPriorityTaskWokenTx = pdFALSE;
	char charToTransmit;

	if (uart->TransmissionAvailable)
	{
		xQueueReceiveFromISR(uart->QueueTxPkg, (void *)&uart->txPkg, &uart->xHigherPriorityTaskWokenTx);
		uart->TransmissionAvailable = false;
	}

	charToTransmit = package_PeekElement(uart->txPkg);
	
	if (charToTransmit != END_STRING)
	{
		/* Send all character in package until end string */
		uartTxWrite(uart->uartValue, charToTransmit);
	}

	/* Final character from package */
	if (charToTransmit == uart->eom)
	{
		txInterruptDisable(uart);

		/* Free memory of transmitted packet */
		QMPool_put_fromISR(&uart->memory, uart->txPkg);
		uart->TransmissionAvailable = true;
		xTimerStartFromISR(uart->onTxTimeOut, &uart->xHigherPriorityTaskWokenTx);
	}

	/* Call scheduler if is nessesary */
	portYIELD_FROM_ISR(uart->xHigherPriorityTaskWokenTx);
}

static void waitForSOMAction(void *object, uint8_t receivedChar)
{
	frame *uart = (frame *)object;

	// ENTRY ----------------------------------------
	if (uart->receiveState->stateHasChanged)
	{
		/* Do nothing here */
		uart->receiveState->stateHasChanged = false;
	}

	// DO    ----------------------------------------
	if (uart->som == receivedChar)
	{
		/* Only change state if som is received */
		ChangeState(uart->receiveState, storeCharAction);
	}

	// EXIT ------------------------------------------
	if (uart->receiveState->stateHasChanged)
	{
		/* Start timer with SOM */
		xTimerStartFromISR(uart->onRxTimeOut, &uart->xHigherPriorityTaskWokenRx);
	}
}

static void storeCharAction(void *object, uint8_t receivedChar)
{
	frame *uart = (frame *)object;

	// ENTRY ----------------------------------------
	if (uart->receiveState->stateHasChanged)
	{
		/* Get memory to manage new package */
		uart->rxPkg = QMPool_get_fromISR(&uart->memory, 0);
		if (NULL == uart->rxPkg)
		{
			/* No memory for package, wait for next */
			ChangeState(uart->receiveState, waitForSOMAction);
			xTimerStopFromISR(uart->onRxTimeOut, &uart->xHigherPriorityTaskWokenRx);
		}
		else
		{
			/* Instantiate package */
			package_ctor(uart->rxPkg, uart->som, uart->eom);
			/* Successful entry */
			uart->receiveState->stateHasChanged = false;
		}
	}

	// DO    ----------------------------------------
	/* Reset timeout in every character received */
	xTimerResetFromISR(uart->onRxTimeOut, &uart->xHigherPriorityTaskWokenRx);

	if ((uart->som != receivedChar) && (uart->eom != receivedChar))
	{
		/* Save all character except SOM and EOM */
		if (!package_addElement(uart->rxPkg, receivedChar))
		{
			/* If package is full go back to wait for som action */
			ChangeState(uart->receiveState, waitForSOMAction);
		}
	}
	else if (uart->eom == receivedChar)
	{
		if (package_check(uart->rxPkg))
		{
			/* Send memory direction of package to queue */
			xQueueSendFromISR(uart->QueueRxPkg, &uart->rxPkg, 0);
		}
		else
		{
			/* If CRC check fail, discard package */
			QMPool_put_fromISR(&uart->memory, uart->rxPkg);
		}

		ChangeState(uart->receiveState, waitForSOMAction);
	}
	else if (uart->som == receivedChar)
	{
		/* SOM restart the process */
		QMPool_put_fromISR(&uart->memory, uart->rxPkg);
		ChangeState(uart->receiveState, storeCharAction);
	}

	// EXIT ------------------------------------------
	if (uart->receiveState->stateHasChanged)
	{
		xTimerStopFromISR(uart->onRxTimeOut, &uart->xHigherPriorityTaskWokenRx);
	}
}

void onRxTimeOutCallback(xTimerHandle pxTimer)
{
	frame *uart = (frame *)pvTimerGetTimerID(pxTimer);

	taskENTER_CRITICAL();

	gpioToggle(LED2);
	/* Discard package */
	QMPool_put(&uart->memory, uart->rxPkg);
	ChangeState(uart->receiveState, waitForSOMAction);
	
	taskEXIT_CRITICAL();
}

void onTxTimeOutCallback(xTimerHandle pxTimer)
{
	frame *uart = (frame *)pvTimerGetTimerID(pxTimer);

    taskENTER_CRITICAL();
	
	if (uxQueueMessagesWaiting(uart->QueueTxPkg))
	{
		txInterruptEnable(uart);
		uartSetPendingInterrupt(uart->uartValue);
	}

	taskEXIT_CRITICAL();
}
