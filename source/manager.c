#include "manager.h"

void insertTextOnQueue(char *text, Queue *f){
    insertOnQueue(createProcess(text), f);
}

void changeToExecution(Queue *fe, Queue *rt, Queue *rr){
    Process *p;
    while(fe->beginning != NULL){
        p = removeFromQueue(fe);
        if(p->priority == 0)
            insertOnQueue(p, rt);
        else
            insertOnQueue(p, rr);
    }
}

void execute(Queue *rt, Queue *rr, List **exec){
    Process *p;
    static int executed = 0;
    int pid;
    int resp;

    if(rt->beginning != NULL){
        while(rt->beginning != NULL){
            p = removeFromQueue(rt);
            pid = fork();
            if(pid == 0){
                system(p->command);
                exit(0);
            }

            else if(pid < 0)
                exit(1);

            else{
                p->id = pid;
                printf("\nProcess with PID %d is being executed on FIFO queue\n", p->id);
                waitpid(p->id, &resp, 0);
                p->executed = 1;
                p->positionOnExecution = ++executed;
                printf("Process with PID %d has been executed\n", p->id);
                *exec = insertOnList(p, *exec);
            }
        }
    }
    
    if(rr->beginning != NULL){
        char batata[30];
        struct stat sts;
        while(rr->beginning != NULL){
            p = removeFromQueue(rr);
            if(p->executed == 0){                
                p->executed = 2;
                signal(SIGCHLD, SIG_IGN);
                pid = fork();
                if(pid == 0){
                    system(p->command);
                    exit(0);
                }
    
                else if(pid < 0){
                    exit(1);
                }

                else{
                    p->id = pid;
                    printf("\nProcess with PID %d is being executed on RR queue\n", p->id);
                    sprintf(batata,"/proc/%d", p->id);
                    sleep(6);
                    resp = kill(p->id, SIGSTOP);                 
                    if(resp == 0 && stat(batata, &sts) != -1)
                        insertOnQueue(p, rr);                    
                    else{                        
                        p->executed = 1;
                        p->positionOnExecution = ++executed;                        
                        *exec = insertOnList(p, *exec);
                        printf("Process with PID %d has been executed\n", p->id);                   
                    }
                }
            }

            else if(p->executed == 2){
                printf("\nProcess with PID %d is being executed on RR queue\n", p->id);
                kill(p->id, SIGCONT);
                sprintf(batata,"/proc/%d", p->id);
                sleep(6);
                resp = kill(p->id, SIGSTOP);
                if(resp == 0 && stat(batata, &sts) != -1)
                    insertOnQueue(p, rr); 
                else{                   
                    p->executed = 1;
                    p->positionOnExecution = ++executed;                        
                    *exec = insertOnList(p, *exec);
                    printf("Process with PID %d has been executed\n", p->id);               
                }
            }
        }
    }
    printf("\nAll the processes on the waiting queue were executed\n");
}

void showInformation(Queue *f, List *exec){
    printf("Executed processes:\n");
    dumpList(exec);
    printf("\n");
    printf("Processes on the waiting queue: \n");
    dumpList(f->beginning);
    printf("\n");
}

void showAllInformation(Queue *f, List *exec){    
    List *temp, *executed = NULL, *nonexecuted = NULL;    
    for(temp = exec; temp != NULL; temp = temp->next){       
        executed = orderByExecution(executed, temp->p);    
    }    
    for(temp = f->beginning; temp != NULL; temp = temp->next){
        nonexecuted = orderByPriority(nonexecuted, temp->p);
    }
    printf("Dump of all queues:\n");
    printf("Executed processes (ordered by execution:\n");
    dumpList(executed);  
    printf("\n");
    printf("Processes on the waiting queue (ordered by priority):\n");
    dumpList(nonexecuted);
    printf("\n");
}

void loadProcessByFile(char *name, Queue *f){
    FILE *file = fopen(name, "r");
    char line[128];
    while(fgets(line,sizeof(line), file)){
        insertTextOnQueue(line, f);
    }
    fclose(file);
}