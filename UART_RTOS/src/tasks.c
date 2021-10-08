//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern    uint8_t dato;

void vTaskReadUART(void* taskParamPtr ){
	while(1){

	}
}

void vTaskWriteUART(void* taskParamPtr ){
	while(1){
		
	}
}

void vTaskUART(void* taskParamPtr){
	while(1){
      // Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
      if(  uartReadByte( UART_USB, &dato ) ){

         // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
         uartWriteByte( UART_USB, dato );
      }		
	}
}