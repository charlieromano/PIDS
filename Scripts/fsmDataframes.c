/*fsmDataframes.c*/
#include "fsmDataframes.h"

evSystemState 	listeningHandler(void){

}
evSystemState 	headerHandler(void);
evSystemState 	scanningHandler(void);
evSystemState 	trailerHandler(void);
evSystemState 	recordingHandler(void);
evSystemState 	discardingHandler(void);


int main (int argc, char** argv)
{
	State_type currState = 0;
	Action_t action;
	char* p = *argv; char symbol;
	int len = strlen(p);
}