/*fsmDataframes.c*/
#include "fsmDataframes.h"

evSystemState 	listeningHandler(void);
evSystemState 	headerHandler(void);
evSystemState 	scanningHandler(void);
evSystemState 	trailerHandler(void);
evSystemState 	recordingHandler(void);
evSystemState 	discardingHandler(void);
