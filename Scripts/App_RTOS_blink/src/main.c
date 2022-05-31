#include "sapi.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "task.h"

DEBUG_PRINT_ENABLE;

SemaphoreHandle_t tecla_pulsada_sem;

TickType_t get_diff();
void clear_diff();
void fsmButtonInit( void );
void fsmButtonUpdate( gpioMap_t tecla );

void tarea_led( void* taskParmPtr );
void tarea_tecla( void* taskParmPtr );

void toggle1(void);
void toggle2(void);

int main( void )
{
    boardConfig();

    debugPrintConfigUart( UART_USB, 115200 );
    debugPrintlnString( "Blinky using non blocking delay" );

    BaseType_t res =
    xTaskCreate( tarea_tecla, ( const char * )"tarea_tecla",   
                 configMINIMAL_STACK_SIZE*2, NULL,
                 tskIDLE_PRIORITY+1, 0
    );

    vTaskStartScheduler();

    while( true );

   return 0;
}

TickType_t xLastWakeTime;

void tarea_tecla( void* taskParmPtr )
{
    extern TickType_t xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

	while( true ){
        toggle1();
        toggle2();


	}
}

void toggle1(void){
    extern TickType_t xLastWakeTime;
        gpioToggle( LEDB );
        vTaskDelayUntil( &xLastWakeTime, 250 / portTICK_RATE_MS );
}

void toggle2(void){
        extern TickType_t xLastWakeTime;
        gpioToggle( LED3 );
        vTaskDelayUntil( &xLastWakeTime, 400 / portTICK_RATE_MS );
}
// Implementacion de funcion de la tarea
void tarea_led( void* taskParmPtr )
{
    gpioMap_t led = (gpioMap_t) taskParmPtr;
    
    while( TRUE )
    {
    	xSemaphoreTake(  tecla_pulsada_sem  ,  portMAX_DELAY );  //esperar tecla

    	TickType_t dif = get_diff();
    	//clear_diff();

		gpioWrite( LED2 , ON );
		vTaskDelay( dif );
		gpioWrite( LED2 , OFF );
    }
}

