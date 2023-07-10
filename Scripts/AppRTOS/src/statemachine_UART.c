//statemachine_UART.c
#include "statemachine_UART.h"

extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

// Globals
static char 			*uart_msg_ptr = NULL;
static char 			uart_received_data;
static uint8_t			uart_buf_idx;
static const uint8_t 	uart_buf_len = UART_BUFFER_LENGTH;
static uint8_t			uart_buf[UART_BUFFER_LENGTH];
volatile bool_t		 	uart_timer_flag;
static volatile bool_t 	uart_msg_flag;

uint8_t uart_received_byte;
uint8_t uart_start_byte 	= UART_START_BYTE;
uint8_t uart_stop_byte 		= UART_STOP_BYTE;

sStateMachine_UART fsmUART[] = 
{
	{STATE_UART_INIT, evUart_Init, uart_initHandler},
	{STATE_UART_IDLE, evUart_Received_byte, uart_idleHandler},
	{STATE_UART_LISTENING,  evUart_Received_byte, uart_listeningHandler},
	{STATE_UART_VALID, evUart_Timeout, uart_processingHandler},
	{STATE_UART_ERROR, evUart_Timeout, uart_errorHandler}
};

eSystemState_UART 	uart_initHandler(void){ 

	//IRQ_UART_Init();

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }
	
	uart_msg_flag 		= false;
	uart_timer_flag 	= false;
	uart_buf_idx		= 0;
	uart_received_data 	= -1;

	// Clear whole buffer
	memset(uart_buf, 0, uart_buf_len);

	//IRQ_UART_Init();

	return STATE_UART_IDLE; 
}

eSystemState_UART 	uart_idleHandler(void){ 
/*
*/
    printf("NOTHING\r\n");
    if (uartReadByte( UART_USB, &uart_received_data ) == true ) {
    	if( uart_received_data 	== uart_start_byte ){

    		printf("SOMETHING\r\n");
    		gpioWrite(LED3, OFF);
    		uart_msg_flag 		= true;
    		uart_buf_idx		= 0;

    		return STATE_UART_LISTENING;
    	}
    	else{

    		uart_msg_flag 		= false;
    		
    		return STATE_UART_IDLE;
    	}
    }
    return STATE_UART_IDLE;
}

eSystemState_UART 	uart_listeningHandler(void){
    
    gpioWrite(LED3, OFF);
    gpioWrite(LEDB, ON);

    //for(int i=0; i< uart_buf_len; i++){

    while(true){

    if (uartReadByte( UART_USB, &uart_received_data ) == true ) {

    	if( uart_received_data 	== uart_start_byte ){

    		uart_msg_flag 		= false;
    		uart_timer_flag 	= true;

    		return STATE_UART_VALID;
    	}

    	if(uart_buf_idx < uart_buf_len - 1){
    		uart_buf[uart_buf_idx] = uart_received_data;
    		uart_buf_idx++;
    	}

    	if(uart_buf_idx >= uart_buf_len -1 ) {
			if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
				printf("Buffer size exceeds UART_BUFFER_LENGTH\r\n");
				xSemaphoreGive(xMutexUART);
			}
			return STATE_UART_ERROR;
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
    			uart_msg_flag = true;
    		}
    		// Reset receive buffer and index counter
    		memset(uart_buf, 0, uart_buf_len);
    		uart_buf_idx = 0;
    		uart_timer_flag = true;

    		return STATE_UART_VALID;
    	}
    }
    }
    //return STATE_UART_IDLE;
}

eSystemState_UART 	uart_processingHandler(void){

    gpioWrite(LEDB, OFF);
    if (uart_msg_flag == true) {
    	if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
    		printf("%s\r\n", uart_msg_ptr);
    		xSemaphoreGive(xMutexUART);
    	}
    	vPortFree(uart_msg_ptr);  
    	uart_msg_ptr 	= NULL;
    }

  	IRQ_UART_Init();

    return STATE_UART_IDLE;
}

eSystemState_UART 	uart_errorHandler(void){

  	IRQ_UART_Init();

    return STATE_UART_IDLE;
}
