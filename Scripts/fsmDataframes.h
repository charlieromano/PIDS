#include 	<stdio.h>

typedef enum {

	STATE_LISTENING,
	STATE_HEADER, 
	STATE_SCANNING,
	STATE_TRAILER, 
	STATE_RECORD,
	STATE_DISCARD

} eSystemState;

typedef enum {

	evReceive,
	evError,
	evHead, 
	evMsg,
	evEOF
	
} eSystemEvent;


evSystemState 	listeningHandler(void);
evSystemState 	headerHandler(void);
evSystemState 	scanningHandler(void);
evSystemState 	trailerHandler(void);
evSystemState 	recordingHandler(void);
evSystemState 	discardingHandler(void);

