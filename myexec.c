/* myexec.c */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;		/* environment info */

main(int argc, char **argv)
     /* argc -- number of arguments */
     /* argv -- an array of strings */
{
    char *argvNew[5];
    int pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        /* child process */
        argvNew[0] = "/bin/ls";
        argvNew[1] = "-l";
        argvNew[2] = NULL;
        if (execve(argvNew[0], argvNew, environ) < 0) {
            fprintf(stderr, "Execve error\n");
            exit(1);
        }
    }
    else {
        /* parent */
	wait(0);		/* wait for the child to finish */
    }
}
