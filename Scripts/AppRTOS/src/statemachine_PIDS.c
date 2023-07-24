//statemachine_PIDS.c
#include "statemachine_PIDS.h"

extern SemaphoreHandle_t    xMutexUART;
volatile bool_t         pids_timer_flag;

/*
   STATE_PIDS_STOPPED,
   STATE_PIDS_HEAD_STATION,
   STATE_PIDS_TRAIN_RUNNING,
   STATE_PIDS_TRAIN_ARRIVING,
   STATE_PIDS_STATION_ARRIVED
   
   evPids_Init,
   evPids_accelEvent,
   evPids_Timeout

   eSystemState_PIDS    pids_initHandler(void);
   eSystemState_PIDS    pids_headStationMessagingHandler(void);
   eSystemState_PIDS    pids_headStationHandler(void);
   eSystemState_PIDS    pids_trainRunningHandler(void);
   eSystemState_PIDS    pids_trainArrivingHandler(void);
   eSystemState_PIDS    pids_stationMessagingHandler(void);

*/

sStateMachine_PIDS fsmPIDS[] = 
{
   {STATE_PIDS_INIT, evPids_Init, pids_initHandler},
   {STATE_PIDS_STOPPED, evPids_accelEvent, pids_headStationMessagingHandler},
   {STATE_PIDS_HEAD_STATION, evPids_Timeout, pids_trainRunningHandler},
   {STATE_PIDS_TRAIN_RUNNING, evPids_Timeout, pids_trainRunningHandler},
   {STATE_PIDS_TRAIN_ARRIVING, evPids_Timeout, pids_trainArrivingHandler},
   {STATE_PIDS_STATION_ARRIVED, evPids_Timeout, pids_stationMessagingHandler},
};

eSystemState_PIDS 	pids_initHandler(void){
   
   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("PIDS INIT: PIDS_STATE_STOPPED.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   return STATE_PIDS_STOPPED;

}

eSystemState_PIDS    pids_headStationMessagingHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("PIDS: HEAD STATION MESSAGE. \r\n");
      xSemaphoreGive(xMutexUART);
   }

   return STATE_PIDS_HEAD_STATION; 

}


eSystemState_PIDS 	pids_headStationHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("PIDS: HEAD STATION. STARTING THE TRAIN JOURNEY.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   return STATE_PIDS_TRAIN_RUNNING;

}

eSystemState_PIDS 	pids_trainRunningHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("PIDS: TRAIN RUNNING. NEXT STATION: ...\r\n");
      xSemaphoreGive(xMutexUART);
   }

   return STATE_PIDS_TRAIN_ARRIVING;

}

eSystemState_PIDS 	pids_trainArrivingHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("PIDS: TRAIN ARRIVING TO STATION ...\r\n");
      xSemaphoreGive(xMutexUART);
   }

   return STATE_PIDS_STATION_ARRIVED;

}

eSystemState_PIDS    pids_stationMessagingHandler(void){

   if (pdTRUE == xSemaphoreTake( xMutexUART, portMAX_DELAY)){
      printf("PIDS: STATION .... MESSAGE.\r\n");
      xSemaphoreGive(xMutexUART);
   }

   return STATE_PIDS_STOPPED; 

}

   