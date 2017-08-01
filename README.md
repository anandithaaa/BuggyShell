# BuggyShell
Given half the code of a buggy shell, I fixed it :)

Description of bugs:
List of Known Bugs

Bug 1: Only the first command works properly

$ ./proj4 
sh201>  ls
codebloacks_proj4  procline.o  proj4_draft.zip  runcommand.o  test_run.c       userin.c
Makefile           proj4       proj4.h          shell.txt     test_run_loop    userin.o
procline.c         proj4.c     runcommand.c     test_run      test_run_loop.c
sh201>  ls
ls: cannot access ls: No such file or directory
sh201>  ls
ls: cannot access ls: No such file or directory
ls: cannot access ls: No such file or directory
sh201>  who
who: extra operand ‘who’
Try 'who --help' for more information.
sh201>  
$
After we start the shell (running proj4 the output from the first command is correct, but all later attempts at running anything fail. HINT: this is a very simple fix, but you need to understand the code for the shell, before you can fix it. Fixing this bug, will make it much easier to observe the behavior of the other bugs and test if the fixes to them are correct.

Bug 2: cd command does not behave as expected

$ ./proj4
sh201>  cd /home
cd: No such file or directory
sh201>  
$
The reason for that is that passing cd as the name of the program to execvp system call fails (this command requires change of the environment and hence it is handled in a different fahion than most other commands that you encountered this semester). The program should, instead, use chdir system call to change the current working directory. (Use the man pages to find out how to use chdir.)

You need to fix this problem by implementing the code that will allow the user to use the cd command in the following three ways:

cd - changes the current working directory to the user's home directory (you will need to use getenv() function to obtain the name of the user's home directory

cd PATH_NAME - changes the current working directory to the one specified by the PATH_NAME (if such directory does not exist, the shell should print an error message and return to the prompt)

cd .. - changes the current working directory to the one that is the parent of the current working directory

Bug 3: exit command does not terminate the shell

This is really a feature request. The exit command is not implemented. We would like to be able to type exit with no parameters to terminate the shell program. Currently the only way to terminate the shell is by typing the end of like (EOF) character on the keyboard (this is done by pressing Ctrl+D).

$ ./proj4 
sh201>  exit
exit: No such file or directory
sh201>  
$

Bug 4: Pressing Ctrl+C should not kill the shell

It is customary that the shell itself should be immune to SIGINT signal (Ctrl+C from the keyboard). Pressing the key combination should terminate a process running in the foreground mode, but not the shell itself. Currently the shell terminates when the user presses Ctrl+C.

$ ./proj4 
sh201>  ls
codebloacks_proj4  procline.c  proj4    proj4_draft.zip  runcommand.c  shell.txt  
test_run.c     test_run_loop.c  userin.o    Makefile           procline.o  
proj4.c  proj4.h          runcommand.o  test_run   test_run_loop  userin.c
sh201>  ^C
$

Bug 5: Background processes are not reaped

The shell supports running processes in the background, but it does not reap such processes properly. All background processes should be reaped (as opposed to becoming zombie processes).

$ ./proj4 
sh201>  ./test_run & 
[Process id 3865]
sh201>  program name: ./test_run 

sh201>  ps
  PID TTY          TIME CMD
 3249 pts/13   00:00:00 bash
 3862 pts/13   00:00:00 proj4
 3865 pts/13   00:00:00 test_run <defunct>
 3870 pts/13   00:00:00 ps
sh201>  
$
