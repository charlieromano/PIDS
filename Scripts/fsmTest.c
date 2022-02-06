/* fsmTest */
#include 	<stdio.h>

typedef enum {
	STATE_INIT,
	STATE_A,
	STATE_B,
	STATE_C
} eSystemState;

typedef enum{
	evInit,
	evAlert,
	evReceive,
	evEOF
} eSystemEvent;

typedef eSystemState (*pfEventHandler)(void);

typedef struct{
	eSystemState 		fsmState;
	eSystemEvent 		fsmEvent;
	pfEventHandler 		fsmHandler;
} sStateMachine;

eSystemState 	InitHandler(void)	{ printf("init;\n");return STATE_A; }
eSystemState 	AlertHandler(void)	{ printf("Alert;\n");return STATE_B; }
eSystemState 	ReceiveHandler(void){ printf("Receive;\n");return STATE_C; }
eSystemState 	EOFHandler(void) 	{ printf("EOF;\n");return STATE_A; }

sStateMachine fsmTest [] = 
{
	{STATE_INIT, evInit, InitHandler},
	{STATE_A, evAlert, AlertHandler},
	{STATE_B, evReceive, ReceiveHandler},
	{STATE_C, evEOF, EOFHandler}
};

int main (int argc, char *argv[])
{
	int i=0;
	eSystemState nextState = STATE_INIT;
	eSystemEvent newEvent;

	int unicode = 65;
	int c;
	//char character = (char)unicode;
	//stringtext = character.ToString();

	while(i<10)
	{
		/*
		event = read_event();
		if((event>=0) && (event < MAX_EVENTS);
		{
			next_state = state_table[state][event]();
			state = next_state;
		}
		*/

		if((c = getchar()) != '\n' && (c = getchar()) != '\r' )
		{
			newEvent++;
			fsmTest[nextState].fsmEvent == newEvent;
			nextState = (*fsmTest[nextState].fsmHandler)();
			i++;
		}
		else
		{
			printf("no condition\n;");
		}
	
	}

	return 0;
}