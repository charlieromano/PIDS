/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/01
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __DISPLAY_LED_H__
#define __DISPLAY_LED_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "timers.h"
#include "semphr.h"

#define     CHAR_LENGTH     8 
#define     DISPLAYLED_ROWS    8   
#define     DISPLAYLED_COLS    8
#define     DISPLAYLED_TIMEOUT_MS   500

#define     RETIRO_TIGRE_STATIONS    17
#define     RETIRO_SUAREZ_STATIONS   1
#define     RETIRO_MITRE_STATIONS    1

#define     MESSAGES_FLICKR_NUMBER     3
#define     MESSAGES_TOTAL_NUMBER     RETIRO_TIGRE_STATIONS

#ifdef __cplusplus
extern "C" {
#endif


void portInit(void);
void displayInit(void);

void vTaskDisplayLed( void *pvParameters );
void vTaskDisplayLedTest( void *pvParameters );

void string_read_to_8x8_bytes_out(uint8_t *str_in, uint8_t strlen, uint8_t *array_out);
void reshape_to_display(uint8_t *buffer_in, uint8_t *buffer_out, uint8_t len_buffer_in, uint8_t len_buffer_out);

void printHexArray(uint8_t *buffer, uint8_t len, uint8_t size);
void printBinaryArray(uint8_t *buffer, uint8_t len, uint8_t size);
void print_bin(unsigned char value);

#ifdef __cplusplus
}
#endif

#endif /* __APPRTOS_H__ */
