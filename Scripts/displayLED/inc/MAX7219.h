/*=============================================================================
 * Copyright (c) 2020, Carlos Germán Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2020/06/07
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __MAX7219_H__
#define __MAX7219_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

const uint8_t max7219_reg_noop        = 0x00;
const uint8_t max7219_reg_digit0      = 0x01;
const uint8_t max7219_reg_digit1      = 0x02;
const uint8_t max7219_reg_digit2      = 0x03;
const uint8_t max7219_reg_digit3      = 0x04;
const uint8_t max7219_reg_digit4      = 0x05;
const uint8_t max7219_reg_digit5      = 0x06;
const uint8_t max7219_reg_digit6      = 0x07;
const uint8_t max7219_reg_digit7      = 0x08;
const uint8_t max7219_reg_decodeMode  = 0x09;
const uint8_t max7219_reg_intensity   = 0x0a;
const uint8_t max7219_reg_scanLimit   = 0x0b;
const uint8_t max7219_reg_shutdown    = 0x0c;
const uint8_t max7219_reg_displayTest = 0x0f;


const uint8_t test_data[]={
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
        0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,

};

const unsigned char CH[] = {
3, 8, 0b0000000, 0b0000000, 0b0000000, 0b0000000, 0b0000000, // space
1, 8, 0b1011111, 0b0000000, 0b0000000, 0b0000000, 0b0000000, // !
3, 8, 0b0000011, 0b0000000, 0b0000011, 0b0000000, 0b0000000, // "
5, 8, 0b0010100, 0b0111110, 0b0010100, 0b0111110, 0b0010100, // #
4, 8, 0b0100100, 0b1101010, 0b0101011, 0b0010010, 0b0000000, // $
5, 8, 0b1100011, 0b0010011, 0b0001000, 0b1100100, 0b1100011, // %
5, 8, 0b0110110, 0b1001001, 0b1010110, 0b0100000, 0b1010000, // &
1, 8, 0b0000011, 0b0000000, 0b0000000, 0b0000000, 0b0000000, // '
3, 8, 0b0011100, 0b0100010, 0b1000001, 0b0000000, 0b0000000, // (
3, 8, 0b1000001, 0b0100010, 0b0011100, 0b0000000, 0b0000000, // )
5, 8, 0b0101000, 0b0011000, 0b0001110, 0b0011000, 0b0101000, // * 
5, 8, 0b0001000, 0b0001000, 0b0111110, 0b0001000, 0b0001000, // +
2, 8, 0b10110000, 0b1110000, 0b0000000, 0b0000000, 0b0000000, // ,
4, 8, 0b0001000, 0b0001000, 0b0001000, 0b0001000, 0b0000000, // -
2, 8, 0b1100000, 0b1100000, 0b0000000, 0b0000000, 0b0000000, // .
4, 8, 0b1100000, 0b0011000, 0b0000110, 0b0000001, 0b0000000, // /
4, 8, 0b0111110, 0b1000001, 0b1000001, 0b0111110, 0b0000000, // 0
3, 8, 0b1000010, 0b1111111, 0b1000000, 0b0000000, 0b0000000, // 1
4, 8, 0b1100010, 0b1010001, 0b1001001, 0b1000110, 0b0000000, // 2
4, 8, 0b0100010, 0b1000001, 0b1001001, 0b0110110, 0b0000000, // 3
4, 8, 0b0011000, 0b0010100, 0b0010010, 0b1111111, 0b0000000, // 4
4, 8, 0b0100111, 0b1000101, 0b1000101, 0b0111001, 0b0000000, // 5
4, 8, 0b0111110, 0b1001001, 0b1001001, 0b0110000, 0b0000000, // 6
4, 8, 0b1100001, 0b0010001, 0b0001001, 0b0000111, 0b0000000, // 7
4, 8, 0b0110110, 0b1001001, 0b1001001, 0b0110110, 0b0000000, // 8
4, 8, 0b0000110, 0b1001001, 0b1001001, 0b0111110, 0b0000000, // 9
2, 8, 0b01010000, 0b0000000, 0b0000000, 0b0000000, 0b0000000, // :
2, 8, 0b10000000, 0b01010000, 0b0000000, 0b0000000, 0b0000000, // ;
3, 8, 0b0010000, 0b0101000, 0b1000100, 0b0000000, 0b0000000, // <
3, 8, 0b0010100, 0b0010100, 0b0010100, 0b0000000, 0b0000000, // =
3, 8, 0b1000100, 0b0101000, 0b0010000, 0b0000000, 0b0000000, // >
4, 8, 0b0000010, 0b1011001, 0b0001001, 0b0000110, 0b0000000, // ?
5, 8, 0b0111110, 0b1001001, 0b1010101, 0b1011101, 0b0001110, // @
4, 8, 0b1111110, 0b0010001, 0b0010001, 0b1111110, 0b0000000, // A
4, 8, 0b1111111, 0b1001001, 0b1001001, 0b0110110, 0b0000000, // 0b
4, 8, 0b0111110, 0b1000001, 0b1000001, 0b0100010, 0b0000000, // C
4, 8, 0b1111111, 0b1000001, 0b1000001, 0b0111110, 0b0000000, // D
4, 8, 0b1111111, 0b1001001, 0b1001001, 0b1000001, 0b0000000, // E
4, 8, 0b1111111, 0b0001001, 0b0001001, 0b0000001, 0b0000000, // F
4, 8, 0b0111110, 0b1000001, 0b1001001, 0b1111010, 0b0000000, // G
4, 8, 0b1111111, 0b0001000, 0b0001000, 0b1111111, 0b0000000, // H
3, 8, 0b1000001, 0b1111111, 0b1000001, 0b0000000, 0b0000000, // I
4, 8, 0b0110000, 0b1000000, 0b1000001, 0b0111111, 0b0000000, // J
4, 8, 0b1111111, 0b0001000, 0b0010100, 0b1100011, 0b0000000, // K
4, 8, 0b1111111, 0b1000000, 0b1000000, 0b1000000, 0b0000000, // L
5, 8, 0b1111111, 0b0000010, 0b0001100, 0b0000010, 0b1111111, // M
5, 8, 0b1111111, 0b0000100, 0b0001000, 0b0010000, 0b1111111, // N
4, 8, 0b0111110, 0b1000001, 0b1000001, 0b0111110, 0b0000000, // O
4, 8, 0b1111111, 0b0001001, 0b0001001, 0b0000110, 0b0000000, // P
4, 8, 0b0111110, 0b1000001, 0b1000001, 0b10111110, 0b0000000, // Q
4, 8, 0b1111111, 0b0001001, 0b0001001, 0b1110110, 0b0000000, // R
4, 8, 0b1000110, 0b1001001, 0b1001001, 0b0110010, 0b0000000, // S
5, 8, 0b0000001, 0b0000001, 0b1111111, 0b0000001, 0b0000001, // T
4, 8, 0b0111111, 0b1000000, 0b1000000, 0b0111111, 0b0000000, // U
5, 8, 0b0001111, 0b0110000, 0b1000000, 0b0110000, 0b0001111, // V
5, 8, 0b0111111, 0b1000000, 0b0111000, 0b1000000, 0b0111111, // W
5, 8, 0b1100011, 0b0010100, 0b0001000, 0b0010100, 0b1100011, // X
5, 8, 0b0000111, 0b0001000, 0b1110000, 0b0001000, 0b0000111, // Y
4, 8, 0b1100001, 0b1010001, 0b1001001, 0b1000111, 0b0000000, // Z
2, 8, 0b1111111, 0b1000001, 0b0000000, 0b0000000, 0b0000000, // [
4, 8, 0b0000001, 0b0000110, 0b0011000, 0b1100000, 0b0000000, // 0backslash
2, 8, 0b1000001, 0b1111111, 0b0000000, 0b0000000, 0b0000000, // ]
3, 8, 0b0000010, 0b0000001, 0b0000010, 0b0000000, 0b0000000, // hat
4, 8, 0b1000000, 0b1000000, 0b1000000, 0b1000000, 0b0000000, // _
2, 8, 0b0000001, 0b0000010, 0b0000000, 0b0000000, 0b0000000, // `
4, 8, 0b0100000, 0b1010100, 0b1010100, 0b1111000, 0b0000000, // a
4, 8, 0b1111111, 0b1000100, 0b1000100, 0b0111000, 0b0000000, // 0b
4, 8, 0b0111000, 0b1000100, 0b1000100, 0b0000000, 0b0000000, // c // JFM MOD.
4, 8, 0b0111000, 0b1000100, 0b1000100, 0b1111111, 0b0000000, // d
4, 8, 0b0111000, 0b1010100, 0b1010100, 0b0011000, 0b0000000, // e
3, 8, 0b0000100, 0b1111110, 0b0000101, 0b0000000, 0b0000000, // f
4, 8, 0b10011000, 0b10100100, 0b10100100, 0b01111000, 0b0000000, // g
4, 8, 0b1111111, 0b0000100, 0b0000100, 0b1111000, 0b0000000, // h
3, 8, 0b1000100, 0b1111101, 0b1000000, 0b0000000, 0b0000000, // i
4, 8, 0b1000000, 0b10000000, 0b10000100, 0b1111101, 0b0000000, // j
4, 8, 0b1111111, 0b0010000, 0b0101000, 0b1000100, 0b0000000, // k
3, 8, 0b1000001, 0b1111111, 0b1000000, 0b0000000, 0b0000000, // l
5, 8, 0b1111100, 0b0000100, 0b1111100, 0b0000100, 0b1111000, // m
4, 8, 0b1111100, 0b0000100, 0b0000100, 0b1111000, 0b0000000, // n
4, 8, 0b0111000, 0b1000100, 0b1000100, 0b0111000, 0b0000000, // o
4, 8, 0b11111100, 0b0100100, 0b0100100, 0b0011000, 0b0000000, // p
4, 8, 0b0011000, 0b0100100, 0b0100100, 0b11111100, 0b0000000, // q
4, 8, 0b1111100, 0b0001000, 0b0000100, 0b0000100, 0b0000000, // r
4, 8, 0b1001000, 0b1010100, 0b1010100, 0b0100100, 0b0000000, // s
3, 8, 0b0000100, 0b0111111, 0b1000100, 0b0000000, 0b0000000, // t
4, 8, 0b0111100, 0b1000000, 0b1000000, 0b1111100, 0b0000000, // u
5, 8, 0b0011100, 0b0100000, 0b1000000, 0b0100000, 0b0011100, // v
5, 8, 0b0111100, 0b1000000, 0b0111100, 0b1000000, 0b0111100, // w
5, 8, 0b1000100, 0b0101000, 0b0010000, 0b0101000, 0b1000100, // x
4, 8, 0b10011100, 0b10100000, 0b10100000, 0b1111100, 0b0000000, // y
3, 8, 0b1100100, 0b1010100, 0b1001100, 0b0000000, 0b0000000, // z
3, 8, 0b0001000, 0b0110110, 0b1000001, 0b0000000, 0b0000000, // {
1, 8, 0b1111111, 0b0000000, 0b0000000, 0b0000000, 0b0000000, // |
3, 8, 0b1000001, 0b0110110, 0b0001000, 0b0000000, 0b0000000, // }
4, 8, 0b0001000, 0b0000100, 0b0001000, 0b0000100, 0b0000000, // ~
};


#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __MAX7219_H__ */
