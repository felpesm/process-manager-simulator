#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "queue.h"

void insertTextOnQueue(char *text, Queue *f);
void changeToExecution(Queue *fe, Queue *rt, Queue *rr);
void execute(Queue *rt, Queue *rr, List **exec);
void showInformation(Queue *f, List *exec);
void loadProcessByFile(char *name, Queue *f);
void showAllInformation(Queue *f, List *exec);