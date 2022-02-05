### UART_RTOS: ejemplo de eco usando la UART y una task con RTOS

En este ejemplo se implementa una tarea usando RTOS que se encarga de escuchar la UART (Universal Asynchronous Receiver-Transmitter) y retransmitir cualquier mensaje recibido. Esta aplicación es conocida típicamente como un eco y sirve para probar la interfaz entre  la PC y la EDU-CIAA usando el puerto serie-USB.

```c
//main.c
#include "main.h"

DEBUG_PRINT_ENABLE;
uint8_t dato  = 0; //variable global

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

    //...
    
   if( xTaskCreate( vTaskEchoUART, "Echo test", 
      configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
    
   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}    
```



La tarea que se crea antes de inicializar el scheduler es muy breve y se muestra en el siguiente fragmento de código.



```c
//tasks.c
#include "tasks.h"		//Api de control de tareas y temporización

extern   uint8_t dato;

void vTaskEchoUART(void* pvParameters){
   // Si recibe un byte de la UART_USB lo guardo en la variable dato.
   // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
	while(1){
      if(  uartReadByte( UART_USB, &dato ) ){
         uartWriteByte( UART_USB, dato );
      }		
	}
}

```

