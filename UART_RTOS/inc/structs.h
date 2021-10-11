#ifndef STRUCTS_H
#define STRUCTS_H

#include "sapi.h"
#include "board.h"

#define ANTIREBOTE_MS 		20
#define REFRESH_TIME_ADC 	50
#define QUEUE_LENGTH 		3

typedef struct{

	uint32_t 	data;
	uint8_t  	id;

} tData;

typedef enum{

	ID_SRC_01,
	ID_SRC_02,
	ID_SRC_03,
	ID_SRC_04

} tDataSource;

typedef enum{

    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING

} fsmButtonState_t;


typedef struct{

	adcMap_t		adcChannel;
	uint16_t		value;

}tConfigADC;


typedef struct{

	spiMap_t		spi;
	uint8_t			data;
	uint32_t		clk;
	gpioMap_t		miso;
	gpioMap_t		mosi;
	gpioMap_t		cs;
	bool_t			cpol;
	bool_t			cpha;

}tConfigSPI;


typedef struct{

	uint16_t		dataOut;
	uint16_t		dataIn;
	uint8_t			counter;
	uint8_t			row;
	uint8_t			col;

}tConfigDataIO;


#endif
