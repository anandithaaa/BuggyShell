#include "proj4.h"
/*
BUG 1: File: Procline
       Line # = 10
       Fix : in Procline, the arg is indexing at a random value that causes none of the commands 
            to execute properly. NARG Initialized to 0 to fix only the first commang working properly. Previously narg just assumed a 
            garbage value at the beginning of each iteration of each loop. 
BUG 2: File: Runcommand
       Line # = 29 onwards
       Fix : A test for whether the cline array's 1st member is cd is performed, then we call getenv and chdir to 
       help change the user's directory to the requested directory.
Bug 3: File: Procline
       Line # = 24 onwards
       Fix : Added a test to see if "exit" was the command being passed in, and handled it by exit(0); when user wanted to 
       exit the shell.
BUG 4: File: Runcommand
       Line # = 11 onwards
       Fix : Pressing the key combination should terminate a process running in the foreground mode, but not the shell itself.
       So  I Added a sigint_handler function in order to test for Control C signal and instead of exiting as is the default 
       condition it just does nothing to the flow of the program, ie ignores the signal. I just have the function say caught 
       SIGINT and NOT exit.
BUG 5: File: Runcommand
       Line # = 20 onwards
       Fix : The shell supports running processes in the background, but it does not reap the processes properly. 
       All background processes should be reaped (as opposed to becoming zombie processes), so I added a test to see if there 
       was a SIGCHILD signal being passed to the parent process in which case I reap the child process that 
       would have otherwise stayed a zombie. The bug was that the program only acknowledged a dead child if it was waiting for 
       it when running in the foreground, to fix this, the kernel will send a signal to the parent when its child is dead, 
       this will then invoke the handler for sigchild and waitpid is used. Since the handler is invoked when the child is 
       already dead, it never really waits it just acknowledges and moves on. 
*/

int main()
{


    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput(  ) != EOF ) {

        procline();
    }
    return 0;
}
