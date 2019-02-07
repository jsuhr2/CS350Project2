#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

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

	if(numLevels = -1)
		numLevels = 1;
	else if(numLevels > 4){
		fprintf(stderr, "Number of levels cannot exceed 4\n");
		return 0;
	}
	if(numChildren = -1)
		numChildren = 1;
	else if(numChildren > 3){
		fprintf(stderr, "Number of children cannot exceed 3\n");
		return 0;
	}
	if((sleepTime = -1) && (inputs.pauseFlag == 0))
		sleepTime = 1;




	return 0;
}
