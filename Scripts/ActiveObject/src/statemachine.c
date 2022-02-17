//statemachine.c
#include "statemachine.h"

extern uint8_t data;

eSystemState 	InitHandler(void){ 
	printf("State Machine Init...\n");
	printf("data:%c \n",data);
	return STATE_LISTENING; 
}

eSystemState 	ListeningHandler(void){ 
	//vcccccccc vb
	printf("STATE_LISTENING:\n");
	printf("data:%c \n",data);
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
	{STATE_LISTENING, evHeader, HeaderHandler},
	{STATE_LISTENING, evTrailer, TrailerHandler},
	{STATE_HEADER, evReceive, ListeningHandler},
	{STATE_TRAILER, evReceive, ListeningHandler}
};
