
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;		/* environment info */
double before,after;
struct rusage usage;
struct timeval  tv;
struct timezone  tz;
int pid;
char cwd[100];

void part1(char* cmd[]){
    gettimeofday(&tv, &tz);
    before = ((double) tv.tv_sec * (double) 1000)  + ((double) tv.tv_usec / (double) 100);
    if ((pid = fork()) < 0) {
        fprintf(stderr, "Fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        /* child process */
        if (execvp(cmd[0], cmd) < 0) {
            fprintf(stderr, "Execve error\n");
            exit(1);
        }
    }
    else {
        /* parent */
        wait(0);                /* wait for the child to finish */
        gettimeofday(&tv, &tz);
        double after = ((double) tv.tv_sec * (double) 1000)  + ((double) tv.tv_usec / (double) 100);
        printf("Wall Clock time in milliseconds: %f\n",after-before);
        getrusage(RUSAGE_SELF, &usage);
        printf("System time in milliseconds: %f\n", ((double) usage.ru_stime.tv_sec * (double) 1000)  + ((double) usage.ru_stime.tv_usec / (double) 100));
        printf("User time in millisecond: %f\n", ((double) usage.ru_utime.tv_sec * (double) 1000)  + ((double) usage.ru_utime.tv_usec / (double) 100));
        printf("Number of minor page faults: %lu\n", usage.ru_minflt);
        printf("Number of major page faults: %lu\n", usage.ru_majflt);
        printf("Number of voluntary context switches: %lu\n", usage.ru_nvcsw);
        printf("Number of involuntary context switches: %lu\n", usage.ru_nivcsw);
        }
}


main(int argc, char **argv){	
    char in[128];
    char* cmd[30];
    char* strarr;
    char* delim = " ";
    char* prompt = "==>"; 

    while(1){
	printf(prompt);
	in[0] = ' ';
	//fgets(in,sizeof(in),stdin);
	scanf(" %[^\n]",in);
	strarr = strtok(in,delim);
	if(!strcmp(strarr,"exit")){
		exit(1);
	}else if(!strcmp(strarr,"cd")){
		strarr = strtok(NULL,delim);
		if(strarr){
			if(!chdir(strarr)){
				printf("Current directory changed to %s\n", getcwd(cwd, 100));
			}else{
				fprintf(stderr,"No such file or directory\n");
			}
		}else{
			chdir("~/");
			printf("Current directory changed to %s\n", getcwd(cwd, 100));
		}
	}else if(!strcmp(strarr,"set")){
		char* p = strtok(NULL,delim);
		char* e = strtok(NULL,delim);
		if(!strcmp(p,"prompt") && !strcmp(e,"=")){
			prompt = strtok(NULL,delim);
		}
	}else{
		int i = 0;
		cmd[i] = strarr; 
		while(cmd[i]!=NULL){
  			 cmd[++i] = strtok(NULL,delim);
		}
		part1(cmd);	
	}
    }
}

