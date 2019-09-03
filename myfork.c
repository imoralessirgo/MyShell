/* myfork.c */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

main(int argc, char *argv[])
     /* argc -- number of arguments */
     /* argv -- an array of strings */
{
    int pid;
    int i;

    /* print out the arguments */
    printf("There are %d arguments\n", argc);
    for (i = 0; i < argc; i++)
	printf("%s\n", argv[i]);

    if ((pid = fork()) < 0) {
	fprintf(stderr, "Fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        /* child process */
        for (i = 0; i < 5; i++)
            printf("child (%d) : %s\n", getpid(), argv[2]);
        exit(0);
    }
    else {
        /* parent */
        for (i = 0; i < 5; i++)
            printf("parent (%d): %s\n", getpid(), argv[1]);
        exit(0);
    }
}
