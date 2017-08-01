//Ananditha Raghunath
#include "proj4.h"

/* shell input line */
int procline(void)
{

    char *arg[MAXARG + 1];  // pointer array for runcommand
	//NARG INITIALIZED: BUG ONE CAUGHT. EVERYTIME THE FUNCTION FROM PROJ4 CALLS THIS, THE NARG SHOULD BE RESET TO 0.
    int narg = 0 ;              // number of arguments 
    int toktype;            // type of token in command
    int type;               // type =  FOREGROUND or BACKGROUND


    while ( 1 ) // loop forever
    {
        // take action according to token type
        switch(toktype = gettok(&arg[narg]))

        {

        case ARG:
			//exit if exit typed BUG CAUGHT AND RESOLVED
            	if(strcmp(*arg, "exit") == 0) 
			exit(0);
		if(narg<MAXARG)
                narg++;
            break;

        case EOL:
        case SEMICOLON:
        case AMPERSAND:
            if(toktype == AMPERSAND)
                type = BACKGROUND;
            else
                type = FOREGROUND;

            if(narg != 0)
            {
                arg[narg] = 0;
                runcommand(arg,type);
            }

            if( toktype == EOL )
		    return;
 //NARG SET TO ZERO HERE TO ALLOW FOR MORE THAN ONE COMMAND LINE ARG TO RUN SIMULT
	narg = 0;
           break;
        }
    }
}
