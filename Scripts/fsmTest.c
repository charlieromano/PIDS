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
	eSystemState 	fsmState;
	eSystemEvent 	fsmEvent;
	pfEventHandler 	fsmEventHandler;
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
/*
   if( argc == 2 ) {
      printf("The argument supplied is %s\n", argv[1]);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }

   int c;

   printf( "Enter a value :");
   c = getchar( );

   printf( "\nYou entered: ");
   putchar( c );

   //return 0;
*/
	eSystemState nextState = STATE_INIT;
	int c;

	while(i<10)
	{
		c = getchar( );
		eSystemEvent newEvent = 1;

		if((c==1)&&(newEvent)
			&& (fsmTest[nextState].fsmEvent == newEvent)
		 	&& (fsmTest[nextState].fsmEventHandler != NULL))
		{
			nextState = (*fsmTest[nextState].fsmEventHandler)();
		}
		else{
			printf("no condition\n;");
		}
		i++;
	
	}

	return 0;
}