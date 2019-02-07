#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct _Node {
	int numLevels;
	int numChildren;
	int pauseFlag;
	int sleepTime;
	int sleepFlag;
	int exitFlag;
};
typedef struct _Node Node;

Node parse(int, const char**);

#endif
