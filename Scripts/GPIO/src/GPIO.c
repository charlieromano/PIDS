/*=============================================================================
 * Copyright (c) 2021, Ing. Carlos German Carreño Romano <charlieromano@gmail.com>
 * All rights reserved.
 * License: bsd-2-clause (see LICENSE.txt)
 * Date: 2021/06/21
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "GPIO.h"
#include "sapi.h"


int main( void )
{
   boardConfig();

   delay_t delay;
   delayConfig( &delay, 5 );// miliseconds

   uint8_t state = OFF;
   uint8_t valor = 0;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      if ( delayRead( &delay ) ){
         if( !state )
            state = ON;
         else
            state = OFF;
         //gpioWrite( GPIO8, state );
         gpioWrite( LED1, state );
         gpioToggle(GPIO8);
      }

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3,  valor );
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}


