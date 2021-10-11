#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "FreeRTOS.h"   //Motor del OS
#include "FreeRTOSConfig.h"
#include "task.h"		//Api de control de tareas y temporizaciÃ³n
#include "semphr.h"		//Api de sincronizaciÃ³n (sem y mutex)
#include "queue.h"      //Api de colas
#include "sapi.h"
#include "board.h"
#include "tasks.h"
#include "structs.h"
#include "udf.h"


static const tData xDataFrame[2] = 
{
	{100, ID_SRC_01},
	{200, ID_SRC_02}
};

#endif 
