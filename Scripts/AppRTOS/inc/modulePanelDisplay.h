#ifndef __MODULEPANELDISPLAY_H__
#define __MODULEPANELDISPLAY_H__

#include "sapi.h"
#include "board.h"
#include <stdio.h>
#include <stdint.h>

typedef struct{
    int         rows;
    int         columns;
    gpioMap_t   *pinout;
    char        *data;
    pfBytesOut  handler;
    pfReshape   shaper;
    pfPrint     printer;
    pfSetPinOut set;
    pfGetPinOut get;
} sModule_t;


typedef void (*pfBytesOut)(uint8_t *str_in, uint8_t strlen, uint8_t *array_out);
typedef void (*pfReshape)(int rows, int columns);
typedef void (*pfPrint)(void)
typedef void (*pfSetPinOut)(*gpioMap_t)
typedef void (*pfGetPinOut)(*gpioMap_t)



void pfBytesOut(uint8_t *str_in, uint8_t strlen, uint8_t *array_out);
void pfReshape(int rows, int columns);
void pfPrint(*pfPrint)(void)
void pfSetPinOut(*gpioMap_t)
void pfGetPinOut(*gpioMap_t)