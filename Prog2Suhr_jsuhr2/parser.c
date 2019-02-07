#include "parser.h"

Node parse(int argc, const char **argv){
	Node inputs;
	inputs.numLevels = -1;
	inputs.numChildren = -1;
	inputs.pauseFlag = 0;
	inputs.sleepTime = -1;
	inputs.sleepFlag = 0;
	inputs.exitFlag = 0;
	int opt;
	while((opt = getopt(argc, argv, "uN:M:ps:")) != -1){
			switch(opt){
				case 'u':
					fprintf(stderr, "prog1tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
					inputs.exitFlag = 1;
					return inputs;
					break;
				case 'N':
					inputs.numLevels = atoi(optarg);
					break;
				case 'M':
					inputs.numChildren = atoi(optarg);
					break;
				case 'p':
					inputs.pauseFlag = 1;
					if(inputs.sleepFlag == 1){
						fprintf(stderr, "Cannot have both -p and -s flags\n");	
						fprintf(stderr, "prog1tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
						inputs.exitFlag = 1;
						return inputs;
					}
					break;
				case 's':
					inputs.sleepTime = atoi(optarg);
					inputs.sleepFlag = 1;
					if(inputs.pauseFlag == 1){
						fprintf(stderr, "Cannot have both -p and -s flags\n");	
						fprintf(stderr, "prog1tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
						inputs.exitFlag = 1;
						return inputs;
					}
					break;
				case '?':
					fprintf(stderr, "prog1tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
					inputs.exitFlag = 1;
					return inputs;
					break;
			}
	}
	return inputs;
}
