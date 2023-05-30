/*=============================================================================
 * Copyright (c) 2022, Ing. Carlos German Carreño Romano <ccarreno@fi.uba.ar>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2022/09/04
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __PORTMAP_H__
#define __PORTMAP_H__

/*=====[Inclusions of public function dependencies]==========================*/


/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/* pinout conversion: connector CONN_2x8 (schematic J4) to displayLED signals */

#define A   HC245_A1_R
#define B   HC245_A2_R
#define C   HC245_A3_R
#define D   HC245_A4_R
#define G1  HC245_B2_L
#define G2  HC245_A5_R
#define R1  HC245_B1_L
#define R2  HC245_B3_L
#define STR HC245_B4_L
#define CLK SRCLK

#define DECO_A0     HC245_A1_R
#define DECO_A1     HC245_A2_R
#define DECO_A2     HC245_A3_R
#define DECO_E2_E2  HC245_A5_R
#define DECO_E3_E1  HC245_A4_R
#define SER_ARR_01  HC245_B1_L
#define SER_ARR_02  HC245_B3_L
#define SRCLK       HC245_B5_L 

#define GND_CONN_J4_01  CONN_J4_01
#define HC245_A1_R      CONN_J4_02
#define GND_CONN_J4_03  CONN_J4_03
#define HC245_A2_R      CONN_J4_04
#define GND_CONN_J4_05  CONN_J4_05
#define HC245_A3_R      CONN_J4_06
#define HC245_A5_R      CONN_J4_07
#define HC245_A4_R      CONN_J4_08
#define HC245_B1_L      CONN_J4_09
#define HC245_B0_L      CONN_J4_10
#define HC245_B3_L      CONN_J4_11
#define HC245_B2_L      CONN_J4_12
#define NC_CONN_J4_13   CONN_J4_13
#define HC245_B4_L      CONN_J4_14
#define GND_CONN_J4_15  CONN_J4_15
#define HC245_B5_L      CONN_J4_16

#define CONN_J4_01 GND
#define CONN_J4_02 GPIO0
#define CONN_J4_03 GND
#define CONN_J4_04 GPIO1
#define CONN_J4_05 GND
#define CONN_J4_06 GPIO3
#define CONN_J4_07 T_COL1
#define CONN_J4_08 GPIO5
#define CONN_J4_09 T_FIL0
#define CONN_J4_10 GPIO7
#define CONN_J4_11 T_FIL3
#define CONN_J4_12 GPIO8
#define CONN_J4_13 T_FIL2
#define CONN_J4_14 T_COL2
#define CONN_J4_15 GND
#define CONN_J4_16 T_FIL1


/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/


/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __APPRTOS_H__ */
