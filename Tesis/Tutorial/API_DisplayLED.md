
# Display LED

# 1. send_row_data()


```C
#include 	"displayLED.h"
#include 	"portmap.h"

void display_send_data(	gpioMap_t *data_pin_array, 
						uint8_t data );

```

#### Summary

Esta función envía datos a un display led matricial usando lógica de registros de desplazamiento.

Los datos se reciben como números enteros de 8 bits y representan el estado de las columnas de la matriz led, para una fila determinada.

Mediante un operador bit a bit se envía a cada columna el estado del bit que corresponde al dato. Por ejemplo, el dato 0x01 (0b00000001) envía a las primeras siete columnas el estado OFF y a la octava columna el estado ON. El número de columnas está determinado por la macro LED_MATRIX_COLUMNS. 

Cada operación bit a bit necesita de un ciclo de clock para transferirse al registro de desplazamiento. Al finalizar el escaneo de todas las columnas, se envía un pulso de habilitación o latch.  

En esta función se definen las siguientes señales de control: 

- clk_pin: el pin de salida al que se mapea la señal de reloj
- latch_pin: el pin de salida al que se mapea la señal de habilitación
- output_pin: el pin de salida por el que se envían los datos en formato SIPO (serial in parallel out)
- output_pin_2: un segundo pin de salida por el que se envían datos SIPO



#### Parameters

| Parámetro | Tipo | Descripción |
| ---- | ---- | ---- |
| data_pin_array | gpioMap_t* | Es el puntero al arreglo de pines GPIO que funcionan como puertos de conexión con la matriz led, en particular de las señales de los registros de desplazamiento. |
| LED_MATRIX_COLUMNS | char* |      |
| data | uint8_t |      |



#### Return values
#### Notes
#### Example
```C
    while(true){

        printf("data: %d\r\n",((output_data++)%64));

        gpioWriteDecoOutput(0);
        display_send_data(data_pin_array, ((output_data++)%64));
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( SCAN_PERIOD / portTICK_RATE_MS ) );

    }
```
#### Source code


```C
void display_send_data(gpioMap_t *data_pin_array, uint8_t data){

    gpioMap_t clk_pin       =   data_pin_array[0];//CLK;//LED2;//SRCLK;
    gpioMap_t latch_pin     =   data_pin_array[1];//G1;//LED1;//STR;
    gpioMap_t output_pin    =   data_pin_array[2];//STR;//LED3;//SER_ARR_01;
    gpioMap_t output_pin_2  =   data_pin_array[3];//STR;//LED3;//SER_ARR_01;

    for (int i=0 ; i<PANEL_COLUMNS; i++){

        printf("loop: i=%d \r\n",i);

        gpioWrite(output_pin_2, (data >> (i%8)) & (0x01));
        gpioWrite(output_pin, (data >> (i%8)) & (0x01));
        
        gpioWrite(clk_pin, ON);
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( CLK_TIME / portTICK_RATE_MS ) );
        gpioWrite(clk_pin, OFF);
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( CLK_TIME / portTICK_RATE_MS ) );

    }

    gpioWrite(latch_pin, ON);
    gpioWrite(latch_pin, OFF);

}

```
# 2. scan_columns()

```C
#include 	"displayLED.h"
#include 	"portmap.h"

void gpioWriteDecoOutput(uint8_t output);

```
#### Summary

Esta función habilita las salidas del decodificador de tres entradas a ocho salidas (deco 3x8).  El orden de activación es el natural. La curata salida en los display leds está cableada con un inversor de por medio entre la lógica de activación cruzada de dos decos.*

#### Parameters

| Parámetro | Tipo | Descripción |
| ---- | ---- | ---- |
#### Return values
#### Notes
#### Example

```C
    while(true){

        printf("data: %d\r\n",((output_data++)%64));

        gpioWriteDecoOutput(0);
        display_send_data(data_pin_array, ((output_data++)%64));
        vTaskDelayUntil( &xLastWakeTimeDisplayLED, ( SCAN_PERIOD / portTICK_RATE_MS ) );

    }
```

#### Source code

```C
void gpioWriteDecoOutput(uint8_t output){

    for(int i=0; i<HALF_PERIOD;i++){

        gpioToggle(deco_pin_array[0]);
    
        if((i%2)==0){        
            gpioToggle(deco_pin_array[1]);
        }
        if((i%4)==0){
            gpioToggle(deco_pin_array[2]);
        }
        if((i%8)==0){
            gpioToggle(deco_pin_array[3]);
        }
    }
}
```

```C
void display_clock_signal(gpioMap_t clock_pin, float32_t period_ms);

```
```C
void display_latch_enable(gpioMap_t latch_pin, float32_t period_ms);

```

```C
void display_deco_signal(void);

```

```C
void display_clock_array(gpioMap_t *clk_array, uint8_t array_len, uint8_t clk_number );

```


```C
void vTaskDisplayLED(void* pvParameters);

```

```C
void displayInit(void);

```


# UART

```C
void UARTInit(void);

```
