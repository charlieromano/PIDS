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


int main( void )
{
    boardConfig();

    debugPrintConfigUart( UART_USB, 115200 );
    debugPrintlnString( "Ejercicio 2_2" );

    gpioWrite( LED2, ON );

    tecla_pulsada_sem = xSemaphoreCreateCounting( 3 , 0 );

    BaseType_t res =
    xTaskCreate( tarea_led, ( const char * )"tarea_led_1",   
                 configMINIMAL_STACK_SIZE*2, (void *)LEDR,
                 tskIDLE_PRIORITY+1, 0
    );

    xTaskCreate(
    	tarea_tecla, ( const char * )"tarea_tecla",   
        configMINIMAL_STACK_SIZE*2,  0, 
        tskIDLE_PRIORITY+1, 0 
    );

    vTaskStartScheduler();

    while( TRUE )
    {

    }

   return 0;
}


void tarea_tecla( void* taskParmPtr )
{
	fsmButtonInit();



	while( 1 )
	{
		fsmButtonUpdate( TEC1 );
	 	vTaskDelay( 1 / portTICK_RATE_MS );
	}
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

