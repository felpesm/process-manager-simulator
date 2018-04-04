#include "queue.h"

Queue* createQueue(void){
    Queue *f = (Queue*)malloc(sizeof(Queue));
    f->beginning = f->end = NULL;
    return f;
}

void insertOnQueue(Process *p, Queue *f){
    List *l = insertOnList(p, NULL);
    if(f->end != NULL)
        f->end->next = l;
    else
        f->beginning = l; 
    f->end = l;
}

Process* removeFromQueue(Queue *f){
    List *temp = f->beginning;
    Process *p = temp->p;
    f->beginning = temp->next;
    if(f->beginning == NULL)
        f->end = NULL;
    free(temp);
    return p;
}

List* insertOnList(Process *p, List *l){
    List *temp = (List*)malloc(sizeof(List));
    temp->p = p;
    temp->next = l;
    return temp;
}

void dumpList(List *l){
    List *temp;
    for(temp = l; temp != NULL; temp = temp->next){
        char executed[5];
        if(temp->p->executed == 1)
            sprintf(executed, "Yes");
        else
            sprintf(executed, "No");
        if(temp->p->id != 0)
            printf("PID: %d | ", temp->p->id);
        printf("Command: %s | User: %s | Priority: %d | Executed: %s | Position on the waiting queue: %d ", temp->p->command, temp->p->user, temp->p->priority, executed, temp->p->positionOnQueue);
        if(temp->p->positionOnExecution != 0)
            printf("| Position on the execution queue: %d", temp->p->positionOnExecution);
        printf("\n");
    }
}

List* orderByPriority(List *l, Process *p){
    List* new;
    List* ant = NULL;
    List *temp;
    for(temp = l; temp != NULL && temp->p->priority < p->priority; temp = temp ->next){
        ant = temp;
    }
    if(temp == NULL){
        for(temp = l; temp != NULL && temp->p->positionOnQueue < p->positionOnQueue; temp = temp ->next){
            ant = temp;
        }
    }
    new = (List*) malloc(sizeof(List));
    new->p = p;
    if (ant == NULL) { 
        new->next = l;
        l = new;
    }
    else { 
        new->next = ant->next; 
        ant->next = new;
    }
    return l;
}

List* orderByExecution(List *l, Process *p){
    List* new;
    List* ant = NULL;
    List *temp;
    for(temp = l; temp != NULL && temp->p->positionOnExecution < p->positionOnExecution; temp = temp->next){
        ant = temp;
    }
    new = (List*) malloc(sizeof(List));
    new->p = p;
    if (ant == NULL) { 
        new->next = l;
        l = new;
    }
    else {
        new->next = ant->next;
        ant->next = new;
    }
    return l;
}
void freeQueue(Queue *f){
    freeList(f->beginning);
    free(f);
}

void freeList(List *l){
    List *p = l;
    while(p != NULL){
        List *t = p->next;
        freeProcess(p->p);
        free(p);
        p = t;
    }
}