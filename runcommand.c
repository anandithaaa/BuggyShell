	   #include "proj4.h"
#include <signal.h>

//Author: Ananditha Raghunath
// execute a command with optional wait
int runcommand(char **cline, int where) {
    pid_t pid;
    int status;

    //sigint handler code written to catch sigint. this fixes Bug 3. Now the code doesn't exit when control c is called, and only the exit command terminates the shell.
    void sigint_handler(int sig) {
	write(1, "Caught SIGINT!\n", 16);
    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
	perror("signal error");
	return 0;
	}
//This code is written to take a sigchild and if the zombie process hasn't been dealt wiht, deals with the bug 5 and terminates the unreaped background processes.
    if (signal(SIGCHLD, sigint_handler) == SIG_ERR) {
	perror("signal error") ;
	return 0;
     }
	
	//THIs line of code fixes the cd command not working. The cd command is implemented 
	//by testing each argument in the command line and using getenv to change the user's 
	//directory using chdir
	
    if(strcmp(cline[0], "cd") == 0) {
	if(cline[1] == 0) {
//		char * HOME = getenv("HOME");
//		char * PWD = getenv("PWD");
		chdir(getenv("HOME"));	
	} else if(chdir(cline[1]) == -1) {
		perror(cline[1]);
	} return;
}
    switch(pid=fork()) {
    case -1:
        perror(SHELL_NAME);
        return (-1);
    case 0:
        execvp(*cline,cline);
        //we should never get to this code, sice execve does not return
        perror(*cline);
        exit(1);
    }
    // code for parent
    // if background process print pid and exit
    // program is running in the background
    if(where == BACKGROUND) {
        printf("[Process id %d]\n",pid);
        return (0);
    }

    // wait until process pid exits
    if (waitpid(pid,&status,0) == -1)
        return (-1);
    else
        return (status);
}
