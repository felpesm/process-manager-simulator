#include "../include/process.h"

Process* createProcess(char *text){
    static int position = 0;
    int i = 0;
    Process *p = (Process*)malloc(sizeof(Process));
    p->user = (char*)malloc(sizeof(char) * 20);
    p->command = (char*)malloc(sizeof(char) * 100);
    p->id = 0;
    char *output = strtok(text, ":"), priority[5];
    while(output != NULL){
        if(i == 0)
            sprintf(p->user, "%s", output);
        else if(i == 1)
            sprintf(p->command, "%s", output);
        else{
            sprintf(priority, "%s", output);
            p->priority = atoi(priority);
        }
        output = strtok(NULL, ":");
        i++;
    }
    p->executed = 0;
    p->positionOnExecution = 0;
    p->positionOnQueue = ++position;
    printf("A process has been added on the waiting queue\n");
    return p;
}

void freeProcess(Process *p){
    free(p->user);
    free(p->command);
    free(p);
}
