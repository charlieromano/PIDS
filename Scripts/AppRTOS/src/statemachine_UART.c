//statemachine_UART.c
#include "statemachine_UART.h"

extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

#define UART_START_BYTE  	0xCC
#define UART_STOP_BYTE  	0xEE
#define UART_BUFFER_LENGTH 	32

// Globals
static char 			*uart_msg_ptr = NULL;
static char 			uart_received_data;
static uint8_t			uart_buf_idx;
static const uint8_t 	uart_buf_len = UART_BUFFER_LENGTH;
static uint8_t			uart_buf[UART_BUFFER_LENGTH];
static volatile uint8_t uart_msg_flag;

uint8_t uart_received_byte;
uint8_t uart_start_byte 	= UART_START_BYTE;
uint8_t uart_stop_byte 		= UART_STOP_BYTE;

sStateMachine_UART fsmUART[] = 
{
	{STATE_UART_INIT, evUart_Init, uart_initHandler},
	{STATE_UART_LISTENING,  evUart_Received_byte, uart_listeningHandler},
	{STATE_UART_PROCESSING, evUart_Received_byte, uart_processingHandler}

};

eSystemState_UART 	uart_initHandler(void){ 

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }

	uart_buf_idx		= 0;
	uart_received_data 	= -1;
	uart_msg_flag 		= 0;

	// Clear whole buffer
	memset(uart_buf, 0, uart_buf_len);

	return STATE_UART_LISTENING; 
}

eSystemState_UART 	uart_listeningHandler(void){

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_LISTENING\r\n");
        xSemaphoreGive(xMutexUART);
    }

    if (uartReadByte( UART_USB, &uart_received_data ) == true ) {
    	
    	if(uart_buf_idx < uart_buf_len - 1){
    
    		uart_buf[uart_buf_idx] = uart_received_data;
    		uart_buf_idx++;
    	}

    	if(uart_buf_idx >= uart_buf_len -1 ) {
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("String enough!\r\n");
        xSemaphoreGive(xMutexUART);
    }

    	}
    	
    	if( uart_received_data == '\n' ){

    		uart_buf[uart_buf_idx - 1] = '\0';
    	
    		if (uart_msg_flag == 0) {
    			
    			uart_msg_ptr = (char *)pvPortMalloc(uart_buf_idx * sizeof(char));
    			
    			if (uart_msg_ptr==NULL){
    				if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
    					printf("Buffer out of memory\r\n");
    					xSemaphoreGive(xMutexUART);
    				}
    			}

    			memcpy(uart_msg_ptr, uart_buf, uart_buf_idx);

    			// Notify other task that message is ready
    			uart_msg_flag = 1;
    		}
    		// Reset receive buffer and index counter
    		memset(uart_buf, 0, uart_buf_len);
    		uart_buf_idx = 0;

    		return STATE_UART_PROCESSING;
    	}
    }

    return STATE_UART_LISTENING;
}

eSystemState_UART 	uart_processingHandler(void){

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_PROCESSING\r\n");
        xSemaphoreGive(xMutexUART);
    }

    if (uart_msg_flag == 1) {
    	uartWriteString(UART_USB, uart_msg_ptr);
    	vPortFree(uart_msg_ptr);
    	uart_msg_ptr 	= NULL;
    	uart_msg_flag = 0;
    }
    
    return STATE_UART_LISTENING;
}
