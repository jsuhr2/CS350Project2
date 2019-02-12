#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void tree(int currLevel, int numChildren){
	if(currLevel == 0)
		pause();
	printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", currLevel, getpid(), getppid());
	for(int i = 0; i < numChildren; i++){
		pid_t childPid = fork();
		if(childPid == -1){
			fprintf(stderr, "Process Creation Failed.\n");
			exit(1);
		}
		if(childPid == 0){
			tree(currLevel - 1, numChildren);
		}
		else{
			wait(NULL);
		}
	}
}

int main(int argc, char const **argv){
	int numLevels = -1;
	int numChildren = -1;
	int sleepTime = -1;
	pid_t pidparent, pid;

	Node inputs = parse(argc, argv);
	if(inputs.exitFlag == 1)
		return 0;

	numLevels = inputs.numLevels;
	numChildren = inputs.numChildren;
	sleepTime = inputs.sleepTime;
	
	if(numLevels == -1)
		numLevels = 1;
	else if(numLevels > 4){
		fprintf(stderr, "Number of levels cannot exceed 4\n");
		return 0;
	}
	if(numChildren == -1)
		numChildren = 1;
	else if(numChildren > 3){
		fprintf(stderr, "Number of children cannot exceed 3\n");
		return 0;
	}
	if((sleepTime == -1) && (inputs.pauseFlag == 0))
		sleepTime = 1;
	
	if(numLevels == 1){
		printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", numLevels, getpid(), getppid());
		if(inputs.pauseFlag == 1)
			pause();
		else if(inputs.sleepFlag == 1)
			sleep(sleepTime);
	}
	printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", numLevels, getpid(), getppid());
	for(int i = 0; i < numChildren; i++){
		pid_t childPid = fork();
		if(childPid == -1){
			fprintf(stderr, "Process Creation Failed.\n");
			exit(1);
		}
		if(childPid == 0){
			if(numLevels > 1){
				char *arguments[7];
				char *command = "./prog2tree";
				if(inputs.pauseFlag == 1){
					arguments[0] = "-N";
					sprintf(arguments[1], "%d", numLevels - 1);
					arguments[2] = "-M";
					sprintf(arguments[3], "%d", numChildren);
					arguments[4] = "-p";
					arguments[5] = NULL;
					arguments[6] = NULL;
				} else{
					arguments[0] = "-N";
					sprintf(arguments[1], "%d", numLevels - 1);
					arguments[2] = "-M";
					sprintf(arguments[3], "%d", numChildren);
					arguments[4] = "-s";
					sprintf(arguments[5], "%d", sleepTime);
					arguments[6] = NULL;
				}
				if(execvp(command, arguments) < 0){
					fprintf(stderr, "ERROR: execvp failed\n");
					exit(1);			
				}
			}
		}
		else{
			wait(NULL);
			printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", numLevels, getpid(), getppid());
		}
	}
	return 0;
}
