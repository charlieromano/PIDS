### UART_RTOS: ejemplo de eco usando la UART y una task con RTOS

En este ejemplo se implementa una tarea usando RTOS que se encarga de escuchar la UART (Universal Asynchronous Receiver-Transmitter) y retransmitir cualquier mensaje recibido. Esta aplicación es conocida típicamente como un eco y sirve para probar la interfaz entre  la PC y la EDU-CIAA usando el puerto serie-USB.

```c
#include "main.h"

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





