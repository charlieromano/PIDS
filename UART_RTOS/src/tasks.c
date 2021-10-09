//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern   uint8_t dato;

void vTaskReadUART(void* taskParamPtr ){
	while(1){

	}
}

void vTaskWriteUART(void* taskParamPtr ){
	while(1){
		
	}
}

void vTaskEchoUART(void* taskParamPtr){
    // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   	// Se reenvia el dato a la UART_USB realizando un eco de lo que llega
	while(1){
      if(  uartReadByte( UART_USB, &dato ) ){
         uartWriteByte( UART_USB, dato );
      }		
	}
}