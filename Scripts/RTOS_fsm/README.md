# RTOS_fsm


[1. Finite State Machine (fsm)](#fsm)

[2. Finite State Machine con RTOS](#fsmRTOS)



## 1. Finite State Machine (fsm) <a name="fsm"></a>

**Ejemplo de máquina de estados usando un arreglo de estructuras [1]**

[1] Ref: https://aticleworld.com/state-machine-using-c/, consultado durante Enero 2022.



En este ejemplo se implementa una máquina de estados sencilla que contiene tres estados. El ejemplo está implementado en C y se puede compilar directamente en el sistema operativo. Tiene como fin introducir conceptualmente la estrategia de máquina de estados con arreglo de estructuras (array of structure).

La máquina de estados se detalla en el siguiente diagrama: a la izquierda su estructura y a la derecha su funcionamiento.

![](../../Pics/fsmTest.png)



Las definiciones de estados, eventos, estructura y handlers se muestra en el código a continuación. Observar que con esta estructura simple y transparente al diseño se logra escala, legibilidad y mantenibilidad. El uso o cambio de  handlers queda explícito por fuera del funcionamiento de la máquina de estados. Este tipo de implementación requiere el diseño previo de la máquina, especificando como se puede ver en el diagrama todo el funcionamiento de la máquina, incluyendo estados y eventos.

```C
// fsm definitions

// Estados
typedef enum {
	STATE_INIT,
	STATE_A,
	STATE_B,
	STATE_C
} eSystemState;

//Eventos
typedef enum{
	evInit,
	evAlert,
	evReceive,
	evEOF
} eSystemEvent;

typedef eSystemState (*pfEventHandler)(void); //puntero a funcion

// State Machine struct
typedef struct{
	eSystemState 		fsmState;
	eSystemEvent 		fsmEvent;
	pfEventHandler 		fsmHandler;
} sStateMachine;

// Handlers
eSystemState 	InitHandler(void)	{ printf("init;\n");return STATE_A; }
eSystemState 	AlertHandler(void)	{ printf("Alert;\n");return STATE_B; }
eSystemState 	ReceiveHandler(void){ printf("Receive;\n");return STATE_C; }
eSystemState 	EOFHandler(void) 	{ printf("EOF;\n");return STATE_A; }

// State Machine Design
sStateMachine fsmTest [] = 
{
	{STATE_INIT, evInit, InitHandler},
	{STATE_A, evAlert, AlertHandler},
	{STATE_B, evReceive, ReceiveHandler},
	{STATE_C, evEOF, EOFHandler}
};

```

Luego la ejecución del código principal resulta en una iteración muy sencilla que actualiza el estado de la máquina de estados según el evento de entrada y direccionando el handler que corresponda según el diseño. En este caso de estudio hay una sola salida por cada estado posible.

```c
// fsmTest.c
#include 	<stdio.h>

// ... fsm definitions ... 

int main (int argc, char *argv[])
{
	int i=0;
	eSystemState nextState = STATE_INIT;
	eSystemEvent newEvent;
	int c;

	while(i<10) //solo para finalizar el ejemplo
	{

		if((c = getchar()) != '\n' && (c = getchar()) != '\r' )
		{
			newEvent++;
			fsmTest[nextState].fsmEvent == newEvent;
			nextState = (*fsmTest[nextState].fsmHandler)();
			i++;
		}
		else
		{
			printf("no condition\n;");
		}
	
	}

	return 0;
}
```

En la siguiente figura se muestra la compilación y ejecución de este ejemplo. Se puede ver que las primeras dos ejecuciones muestran "no condition", dado que se presionó enter ("\n") dos veces seguidas, cayendo el programa fuera de la condición de actualización de la máquina de estados. Luego se ingresó 1, 2, ... y así hasta finalizar los 10 pasos del ciclo while() especificado. Observar que en cada iteración el handler va cambiando y sólo imprime un mensaje y actualiza el estado de la máquina.



![](../../Pics/fsmTest_run.png)



## 2. Finite State Machine con RTOS <a name="fsmRTOS"></a>

**Ejemplo de máquina de estados usando un arreglo de estructuras con RTOS**

En este ejemplo se implementa en RTOS la máquina de estados diseñada en el apartado anterior. Esta máquina de tres estados queda embebida en una tarea del sistema operativo y a modo de ejemplo se actualiza sólo cinco veces para luego ser eliminada. Una vez que la máquina deja de actualizarse por haberse eliminado la tarea que la maneja, el sistema operativo pasa a estado idle. Notar que para esta tarea se ha configurado el stack con el doble de tamaño que lo usual. Esto es debido a errores de Application Stack Overflow observados durante el desarrollo. 

Usando la misma estrategia de abstracción para la definición de la máquina de estados como array de estructuras y sus handlers asociados, la estructura de la aplicación resulta como se muestra en el siguiente arbol de archivos:

```bash
RTOS_fsm
├── config.mk
├── inc
│   ├── FreeRTOSConfig.h
│   ├── main.h
│   ├── statemachine.h
│   ├── tasks.h
│   └── udf.h
├── LICENSE.txt
├── out
│   ├── libs
│   ├── linker-params
│   ├── RTOS_fsm.bin
│   ├── RTOS_fsm.elf
│   └── RTOS_fsm.map
├── README.md
├── RTOS_fsm
│   └── src
└── src
    ├── main.c
    ├── statemachine.c
    ├── tasks.c
    └── udf.c
```
Observar que el directorio de los include tiene ahora la definición de la máquina de estados como un header y el directorio src contiene su implementación. De esta forma se logra mantenibilidad y se puede cambiar la implementación de los handlers de forma independiente. Las tareas ahora van a tener que incluir estas definiciones de máquinas de estado. 

El archivo principal (main.c) sigue resultando compacto, se define un handler de la tarea que contiene la máquina de estados para luego referenciar la tarea de forma externa:


```C
//main.c
#include "main.h"


DEBUG_PRINT_ENABLE;
uint8_t dato  = 0; //variable global

xTaskHandle xTaskStateMachineHandler; //Handler para eliminar la tarea

int main(void)
{

   boardConfig();
   debugPrintConfigUart( UART_USB, 115200 );

   if( xTaskCreate( vTaskStateMachine, "State Machine test", 
      configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, &xTaskStateMachineHandler) 
      == pdFAIL ) {
      perror("Error creating task");
      return 1;
   }

   vTaskStartScheduler();   // Scheduler

   while(1);

   return 0;
}
```
El archivo de tareas contiene la inicialización de la máquina de estados y la actualización de la misma usando la estrategia de arreglo de estructuras con punteros a función. Observar que la tarea pasa a estado bloqueado cada 50 milisegundos, y pasadas las cinco ejecuciones se elimina la tarea.

```C
//tasks.c
#include "tasks.h"		//Api de control de tareas y temporizaciÃ³n

extern uint8_t dato;
extern sStateMachine fsmTest[];
extern xTaskHandle xTaskStateMachineHandler;

void vTaskStateMachine(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	eSystemState nextState = STATE_INIT;
	eSystemEvent newEvent;
	int i=0;

	while(1){
		while(i<5){ //ejecuto cinco veces la actualización de la máquina de estados

			if(uartReadByte( UART_USB, &dato ))
			{
				if( (dato!= '\n') && (dato != '\r' ) )
				{
					newEvent++;
					fsmTest[nextState].fsmEvent == newEvent;
					nextState = (*fsmTest[nextState].fsmHandler)();
					i++;
				}
			}
			else //si no hay nada para leer, paso a estado blocked por un tiempo de 50 ms
			{
				vTaskDelayUntil(&xLastWakeTime, (50/portTICK_RATE_MS));
			}
		}
		//Pasadas cinco ejecuciones o cambios de estado, elimino la tarea StateMachine.
		vPrintString("This task is running and about to delete itself.\r\n");
		vTaskDelete(xTaskStateMachineHandler);
	}
}

```
El resultado de la ejecución se muestra a continuación. Observar que se ingresan sucesivamente los valores 1, 2, 3, 4, 5 y 6 y en este último la tarea ya ha sido eliminado, por lo que no se observa respuesta ya que el sistema quedó en estado IDLE.

![](../../Pics/fsmTestRTOS_run.png)

Por completitud y dado que hay leves modificaciones respecto del ejemplo anterior, se muestran los archivos que corresponden a la definición de la máquina de estados.


```C
//statemachine.h
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "sapi.h"
#include "board.h"


#include 	<stdio.h>

typedef enum {
	STATE_INIT,
	STATE_A,
	STATE_B,
	STATE_C
} eSystemState;

typedef enum{
	evInit,
	evAlert,
	evReceive,
	evEOF
} eSystemEvent;

typedef eSystemState (*pfEventHandler)(void);

typedef struct{
	eSystemState 		fsmState;
	eSystemEvent 		fsmEvent;
	pfEventHandler 		fsmHandler;
} sStateMachine;

eSystemState 	InitHandler(void)	;
eSystemState 	AlertHandler(void)	;
eSystemState 	ReceiveHandler(void);
eSystemState 	EOFHandler(void) 	;


#endif

```

```C
//statemachine.c
#include "statemachine.h"


eSystemState 	InitHandler(void)	{ printf("init;\n");return STATE_A; }
eSystemState 	AlertHandler(void)	{ printf("Alert;\n");return STATE_B; }
eSystemState 	ReceiveHandler(void){ printf("Receive;\n");return STATE_C; }
eSystemState 	EOFHandler(void) 	{ printf("EOF;\n");return STATE_A; }

sStateMachine fsmTest [] = 
{
	{STATE_INIT, evInit, InitHandler},
	{STATE_A, evAlert, AlertHandler},
	{STATE_B, evReceive, ReceiveHandler},
	{STATE_C, evEOF, EOFHandler}
};
```


**Ejemplo de Objetos Activos con máquinas de estado en RTOS [2]**

[2] Ref: https://www.sinelabore.de/doku.php/wiki/howto/rtos
