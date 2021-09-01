/*=============================================================================
 * Copyright (c) 2021, Ing. Carlos German Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2021/08/03
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "LED.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   // ----- Repeat for ever -------------------------
   while( true ) {
      gpioToggle(LED);
      delay(500);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
