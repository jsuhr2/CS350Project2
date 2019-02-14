#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const **argv){
	int numLevels = -1;
	int numChildren = -1;
	int sleepTime = -1;

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
	} else if(numLevels < 1){
		fprintf(stderr, "Number of levels cannot be less than 1\n");
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
	
	printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", numLevels, getpid(), getppid());

	if(numLevels == 1){
		if(inputs.pauseFlag == 1)
			pause();
		else if(inputs.sleepFlag == 1)
			sleep(sleepTime);
	} else{
		for(int i = 0; i < numChildren; i++){
			int childPid = fork();
			if(childPid == -1){
				fprintf(stderr, "Process Creation Failed.\n");
				exit(1);
			}
			if(childPid == 0){
				char levels[64];
				char children[64];
				char sleep[64];
				sprintf(levels, "%d", numLevels - 1);
				sprintf(children, "%d", numChildren);
				sprintf(sleep, "%d", sleepTime);
				if(inputs.pauseFlag == 1){
					char *arguments[] = {"./prog2tree", "-N", levels, "-M", children, "-p", NULL};
					execvp(arguments[0], arguments);
				} else{
					char *arguments[] = {"./prog2tree", "-N", levels, "-M", children, "-s", sleep, NULL};
					execvp(arguments[0], arguments);
				}
			}
			else{
				wait(NULL);
			}
		}
	}
	printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", numLevels, getpid(), getppid());
	return 0;
}
