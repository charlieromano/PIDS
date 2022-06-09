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

TickType_t xLastWakeTime_1;

void tarea_tecla( void* taskParmPtr )
{


    xLastWakeTime_1 = xTaskGetTickCount();

	while( true ){

        for(int i=0; i<4; i++){
            toggle1();
        }

        toggle2();
	}
}

void toggle1(void){
extern TickType_t xLastWakeTime_1;

        gpioWrite(LEDB, ON);
        vTaskDelayUntil( &xLastWakeTime_1, 100 / portTICK_RATE_MS );
        gpioWrite(LEDB, OFF);
        vTaskDelayUntil( &xLastWakeTime_1, 100 / portTICK_RATE_MS );
}

void toggle2(void){
extern TickType_t xLastWakeTime_2;

        gpioWrite(LED1, ON);
        vTaskDelayUntil( &xLastWakeTime_1, 500 / portTICK_RATE_MS );
        gpioWrite(LED1, OFF);
        vTaskDelayUntil( &xLastWakeTime_1, 500 / portTICK_RATE_MS );

}
