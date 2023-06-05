//statemachine_UART.c
#include "statemachine_UART.h"

extern QueueHandle_t        queueHandle_displayLed;
extern SemaphoreHandle_t    xMutexUART;

#define UART_START_BYTE  	0xCC
#define UART_STOP_BYTE  	0xEE
#define UART_BUFFER_LENGTH 	16

uint8_t received_byte;
uint8_t start_byte 	= UART_START_BYTE;
uint8_t stop_byte 	= UART_STOP_BYTE;

sStateMachine_UART fsmUART[] = 
{
	{STATE_UART_INIT, evUart_Init, uart_initHandler},
	{STATE_UART_IDLE, evUart_Rx, uart_idleHandler},
	{STATE_UART_LISTENING, evUart_Rx, uart_listeningHandler},
	{STATE_UART_DATA, evUart_Rx, uart_dataHandler},
	{STATE_UART_STOP, evUart_Rx, uart_stopHandler},
	{STATE_UART_ERROR, evUart_Rx, uart_errorHandler}

};

// Globals
static int initFrame, endFrame;
static const uint8_t UART_buf_len = UART_BUFFER_LENGTH;
static int UART_rx_data;

static char *UART_msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;

uint8_t UART_idx;
char UART_buf[UART_buf_len];

eSystemState_UART 	initHandler_UART(void){ 

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }

	// Clear whole buffer
	UART_idx		= 0;
	UART_rx_data 	= -1;
	memset(UART_buf, 0, UART_buf_len);

	return STATE_UART_IDLE; 
}

eSystemState_UART 	listeningHandler(void){

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_IDLE\r\n");
        xSemaphoreGive(xMutexUART);
    }

	/* while listening check if valid 
	 * if valid then record and process
	 * otherwise keep listening
	 */

    if (uartReadByte( UART_USB, &UART_rx_data ) == true ) {

    	if( UART_rx_data == UART_START_BYTE ){

    		return STATE_UART_LISTENING;
    	}
    }

     	if(UART_idx < UART_BUFFER_LENGTH - 1){
    		UART_buf[UART_idx] = UART_rx_data;
    		UART_idx++;
    	}
    	receiveBuffer = (uint8_t*)malloc(receiveBufferSize);
        UART_msg_ptr = (char *)pvPortMalloc(UART_idx * sizeof(char));

    	

  while (true) {
    uint8_t c_data=0;
 
    // Read cahracters from serial
    if (uartReadByte( UART_USB, &c_data ) == true ) {

      // Create a message buffer for print task
      if (c_data == '\n') {

        // The last character in the string is '\n', so we need to replace
        // it with '\0' to make it null-terminated
        buf[idx - 1] = '\0';

        // Try to allocate memory and copy over message. If message buffer is
        // still in use, ignore the entire message.
        if (msg_flag == 0) {
          UART_msg_ptr = (char *)pvPortMalloc(idx * sizeof(char));
          // If malloc returns 0 (out of memory), throw an error and reset
          //configASSERT(UART_msg_ptr);
         if (UART_msg_ptr==NULL){
            if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
               printf("Buffer out of memory\r\n");
               xSemaphoreGive(xMutexUART);
            }
         }

          // Copy message
          memcpy(UART_msg_ptr, buf, idx);

          // Notify other task that message is ready
          msg_flag = 1;
        }

        // Reset receive buffer and index counter
        memset(buf, 0, buf_len);
        idx = 0;
      }
    }

 

/*
	// Buffer scanning 
	if((initFrame==-1) || (endFrame==-1)){
		for(int i=0; i<DATA_ARRAY_LENGTH; i++){
			if(data_array_copy[i] & MASK_HEADER)
				initFrame=i;
			if(data_array_copy[i] & MASK_TRAILER)
				endFrame=i;
		}
	}

	// State's changing 	

	// case init but no end 
	if( (initFrame!=-1) && (endFrame==-1)){
		memcpy(&output_array_copy,&data_array_copy[initFrame], 
			MAX_BUFFER_SIZE - initFrame); 
		return STATE_UART_LISTENING;
	}

	// case init and end 
	if( (initFrame!=-1) && (endFrame!=-1)){
		memcpy(&output_array_copy,&data_array_copy[initFrame], 
			MAX_BUFFER_SIZE - initFrame - endFrame); 
		return STATE_UART_PROCESSING;
	}

	// case no init neither end 
	if( (initFrame==-1) && (endFrame==-1)){
		memcpy(&output_array_copy[MAX_BUFFER_SIZE - initFrame],&data_array_copy, 
			MAX_BUFFER_SIZE - endFrame); 
		return STATE_UART_PROCESSING;
	}
	else
*/
		return STATE_UART_IDLE;
}

/*
// Settings
static const uint8_t buf_len = 16;

// Globals
static char *UART_msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;

void vTaskReadSerial(void *parameters) {
  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  // Clear whole buffer
  memset(buf, 0, buf_len);
  
  // Loop forever
  while (true) {

    uint8_t c_data=0;
 
    // Read cahracters from serial
    if (uartReadByte( UART_USB, &c_data ) == true ) {
     // dato
     // uartWriteByte( UART_USB, c_data );
     // uartWriteString( UART_USB, "\r\n" );

      // Store received character to buffer if not over buffer limit
      if (idx < buf_len - 1) {
        buf[idx] = c_data;
        idx++;
      }

      // Create a message buffer for print task
      if (c_data == '\n') {

        // The last character in the string is '\n', so we need to replace
        // it with '\0' to make it null-terminated
        buf[idx - 1] = '\0';

        // Try to allocate memory and copy over message. If message buffer is
        // still in use, ignore the entire message.
        if (msg_flag == 0) {
          UART_msg_ptr = (char *)pvPortMalloc(idx * sizeof(char));
          // If malloc returns 0 (out of memory), throw an error and reset
          //configASSERT(UART_msg_ptr);
         if (UART_msg_ptr==NULL){
            if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
               printf("Buffer out of memory\r\n");
               xSemaphoreGive(xMutexUART);
            }
         }

          // Copy message
          memcpy(UART_msg_ptr, buf, idx);

          // Notify other task that message is ready
          msg_flag = 1;
        }

        // Reset receive buffer and index counter
        memset(buf, 0, buf_len);
        idx = 0;
      }
    }
void vTaskWriteSerial(void *parameters) {
  while (true) {
    if (msg_flag == 1) {
      uartWriteString(UART_USB, UART_msg_ptr);
      uartWriteString( UART_USB, "\r\n" );

      vPortFree(UART_msg_ptr);
      UART_msg_ptr = NULL;
      msg_flag = 0;
    }
  }
}
  }
}
*/

eSystemState_UART 	recordingHandler(void){

    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }


	return STATE_UART_PROCESSING;

}


eSystemState_UART 	processingHandler(void){ 
    if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
        printf("STATE_UART_INIT\r\n");
        xSemaphoreGive(xMutexUART);
    }
	return STATE_UART_IDLE;

}
