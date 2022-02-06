# UART_RTOS

[1. Eco UART](#echo)

[2. Two tasks](#2tasks)

[3. Two senders, one receiver](#2senders1receiver)


## 1. Eco UART <a name="echo"></a>

**Ejemplo de eco usando la UART y una task con RTOS**

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



### 2. Two tasks <a name="2tasks"></a>

**Dos tareas escribiendo en la UART**

En este ejemplo dos tareas hacen uso de la UART e imprimen un mensaje. El prototipo de la tarea es único y se crean distintas tareas usando un argumento distinto. El argumento es el mensaje a imprimirse en la UART. En cada ejecución, las tareas quedan en estado bloqueado durante un tiempo determinado manualmente usando la api vTaskDelayUntil(), logrando de esta manera que las tareas se ejecuten periódicamente usando intervalos de tiempo definidos por el usuario.



```C
//main.c

#include "main.h"

DEBUG_PRINT_ENABLE;

static const char *pcMsgTask1 = "Task1 msg\n";
static const char *pcMsgTask2 = "Task2 msg\n";

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   //Option 2: two taks writing the UART
   if( xTaskCreate( vTaskWriteUART, "write UART", 
      configMINIMAL_STACK_SIZE, (void*)pcMsgTask1, 
      tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   if( xTaskCreate( vTaskWriteUART, "write UART2", 
      configMINIMAL_STACK_SIZE, (void*)pcMsgTask2, 
      tskIDLE_PRIORITY+1, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}

```



La tarea que escribe en la UART usa un delay de la api de RTOS que permite al scheduler mantenerla en estado bloqueado y despertarla cuando se cumple el período de tiempo definido en el argumento, en este caso 500 ms: (500/portTICK_RATE_MS).

```C
//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

void vTaskWriteUART(void* pvParameters ){
	// recibe como parámetro un string y lo imprime
	// se bloquea y espera 500 milisegundos
	// la tarea se vuelve periódica con este delay
	char	 *pcTaskMessage;
	pcTaskMessage = (char*)pvParameters;
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while(1){
		if(pcTaskMessage!=NULL){
			uartWriteString( UART_USB, (char*)pcTaskMessage );
		}
		vTaskDelayUntil(&xLastWakeTime, (500/portTICK_RATE_MS));
	}
}

```





### 3. Two senders, one receiver <a name="2senders1receiver"></a>

**Dos tareas que envían mensajes a la UART y una tarea que los recibe**

En este ejemplo se define una tarea vTaskSender() y una tarea vTaskReceiver(). La tarea sender usa una cola (queue) compartida, entonces se pueden crear más de una tarea que escriba en la misma cola. Luego la tarea receiver se encarga de quitar de la cola cualquier elemento que se escribe en ella ni bien se escriba algún dato. Con la definición de sender se crean dos instancias de tareas en el scheduler.

```C
//main.c
#include "main.h"

DEBUG_PRINT_ENABLE;

SemaphoreHandle_t    mutexUART; //Mutex que protege la UART de concurrencia
SemaphoreHandle_t    mutexSPI;

QueueHandle_t xQueue;

static const char *pcMsgTask1 = "Task1 msg\n";
static const char *pcMsgTask2 = "Task2 msg\n";

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   //Option 3: two senders, one receiver
   if( xTaskCreate( vTaskSender, "SENDER 1", 
      configMINIMAL_STACK_SIZE, (tData*)&(xDataFrame[0]), 
      tskIDLE_PRIORITY+2, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
   
   if( xTaskCreate( vTaskSender, "SENDER 2", 
      configMINIMAL_STACK_SIZE, (tData*)&(xDataFrame[1]), 
      tskIDLE_PRIORITY+2, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }
   
   if( xTaskCreate( vTaskReceiver, "RECEIVER", 
      configMINIMAL_STACK_SIZE*2, NULL, 
      tskIDLE_PRIORITY+2, 0) == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}

```



Las tareas sender y receiver utilizan una cola (xQueue) definida en el main e instanciada como extern. En este ejemplo se envía a la cola la estructura de datos recibida como parámetro y se espera una cantidad determinada de ticks del sistema (100 ticks). La tarea receptora también define un tiempo de espera en ticks pero en este caso de 0 ms, es decir que todo el tiempo estará revisando si la cola se llenó con datos. Para este ejemplo se usa una estructura de datos que define un ID de sender, y entonces la tarea revisa el argumento en la cola e imprime un mensaje con el nombre del sender. La api xQueueReceive se encarga también de quitar de la cola al elemento recibido, y en este caso hay un chequeo del largo total de la cola (QUEUE_LENGTH).



```C
//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern   uint8_t dato;
extern   QueueHandle_t xQueue;

void vTaskSender(void* pvParameters ){
	
	BaseType_t 	status;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );

	while(1){
		status = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);
		if(status != pdPASS){
			vPrintString("Couldn't send to the Queue.\r\n");
		}
	}
}

void vTaskReceiver(void* pvParameters ){

	tData 	y;
	BaseType_t status;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 0 );

	while(1){

		if( uxQueueMessagesWaiting(xQueue) != QUEUE_LENGTH ){
			vPrintString("Queue should have been full!\r\n");
		}

		status = xQueueReceive(xQueue, &y, xTicksToWait);

		if(status == pdPASS){
			if(y.id == ID_SRC_01){
				vPrintStringAndNumber("From ID_SRC_01: ", y.data);
			}
			else{
				vPrintStringAndNumber("From ID_SRC_02: ", y.data);
			}
		}
		else{
			vPrintString("Couldn't receive from the Queue.\r\n");
		}
		
	}
}
```

