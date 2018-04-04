#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>

typedef struct process{
	pid_t id;
	char *user;
    int priority;
	char *command;
	int executed;
	int positionOnQueue;
	int positionOnExecution;
} Process;

Process* createProcess(char *text);
void freeProcess(Process *p);