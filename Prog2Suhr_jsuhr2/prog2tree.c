#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

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
	
	if(numLevels == 0)
		pause();
	printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", numLevels, getpid(), getppid());
	for(int i = 0; i < numChildren; i++){
		pid_t childPid = fork();
		if(childPid == -1){
			fprintf(stderr, "Process Creation Failed.\n");
			exit(1);
		}
		if(childPid == 0){
			execlp("/bin/sh", "./prog2tree", "-N", (numLevels - 1), "-M", numChildren, (char *)NULL);
		}
		else{
			wait(NULL);
		}
	}

/*	
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork failed.\n");
		return 1;
	}
	
	if(pid == 0){
		execlp("/bin/ls", "ls", NULL);
	} else{
		wait(NULL);
		printf("Child Complete.\n");
	}
*/
	return 0;
}
