//statemachine.c
#include "statemachine.h"

eSystemState 	InitHandler(void){ 
	printf("State Machine Init...\n");
	printf("data:%d \n",data);
	return STATE_LISTENING; 
}

eSystemState 	ListeningHandler(void){ 

	printf("STATE_LISTENING:\n");
	printf("data:%d \n", data);
	if(data==HEADER){
		printf("HEADER received:\n");
		return STATE_HEADER;
	}
	else if(data==TRAILER){
		printf("TRAILER received:\n");
		return STATE_TRAILER;
	}
	else
	{
		printf("default STATE:\n");
		return STATE_LISTENING; 
	}
}

eSystemState 	HeaderHandler(void){
	printf("STATE_HEADER;\n");
	return STATE_LISTENING; 
}
eSystemState 	TrailerHandler(void){ 
	printf("STATE_TRAILER;\n");
	return STATE_LISTENING; 
}

sStateMachine fsmTest [] = 
{
	{STATE_INIT, evInit, InitHandler},
	{STATE_LISTENING, evReceive, ListeningHandler},
	{STATE_HEADER, evReceive, HeaderHandler},
	{STATE_TRAILER, evReceive, TrailerHandler}
};
