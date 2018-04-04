#include "process.h"

typedef struct list{
    Process *p;
    struct list *next;
} List;

typedef struct queue{
    List *beginning;
    List *end;
} Queue;

Queue* createQueue(void);
void insertOnQueue(Process *p, Queue *f);
Process* removeFromQueue(Queue *f);
List* insertOnList(Process *p, List *l);
void dumpList(List *l);
List* orderByPriority(List *l, Process *p);
List* orderByExecution(List *l, Process *p);
void freeQueue(Queue *f);
void freeList(List *l);