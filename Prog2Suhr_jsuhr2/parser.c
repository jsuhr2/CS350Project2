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
					for(int i = 0; optarg[i] != '\0'; i++){
						if(isdigit(optarg[i]) == 0){
							fprintf(stderr, "Incorrect argument for number of levels\n");
							inputs.exitFlag = 1;
							break;
						}
					}
					inputs.numLevels = atoi(optarg);
					break;
				case 'M':
					for(int i = 0; optarg[i] != '\0'; i++){
						if(isdigit(optarg[i]) == 0){
							fprintf(stderr, "Incorrect argument for number of children\n");
							inputs.exitFlag = 1;
							break;
						}
					}
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
