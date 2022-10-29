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

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "sapi.h"
#include "timers.h"
#include "semphr.h"

#include "portmap.h"


/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/


/*=====[Prototypes (declarations) of public functions]=======================*/

void portInit(void);
void displayInit(void);

void vTaskDisplayLed( void *pvParameters );
void vTaskDisplayLedTest( void *pvParameters );
void string_read_to_8x8_bytes_out(uint8_t *str_in, uint8_t strlen, uint8_t *array_out);

void msgToData(uint8_t *str_in, uint8_t strlen, uint8_t *array_out);

void dataToPanelRows(uint8_t *array_in, uint8_t array_len, uint8_t *rows_out);

void panelRowsToDisplayEncode(uint8_t *panel_in, uint8_t panel_len, uint8_t *display_out);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __APPRTOS_H__ */
