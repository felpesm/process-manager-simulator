#include "manager.h"

int main(){
    int resp;
    Queue *waiting = createQueue(), *realtime = createQueue(), *rr = createQueue();
    List *executed = NULL;
    char text[100];
    while(1){
        printf(" 1 - Put a process to be executed\n 2 - Load a file with processes\n 3 - Execute all processes on the waiting queue\n 4 - Show all processes on the waiting queue and the ones who has been executed\n 5 - Show the same processes, but ordered\n 6 - Exit\n");
        scanf("%d", &resp);
        if(resp == 1){
            printf("Enter with the process's attributes: (user):(command):(priority)\n");
            scanf(" %[^\n]", text);
            insertOnQueue(createProcess(text), waiting);
        }

        else if(resp == 2){
            char file[30];
            printf("Enter with the file's name or path\n");
            scanf("%s", file);
            loadProcessByFile(file, waiting);
        }
 
        else if(resp == 3){
            changeToExecution(waiting, realtime, rr);
            execute(realtime, rr, &executed);
        }

        else if(resp == 4){
            showInformation(waiting, executed);
        }
        
        else if(resp == 5){
            showAllInformation(waiting, executed);
        }

        else if(resp == 6){
            showInformation(waiting, executed);
            showAllInformation(waiting, executed);
            freeQueue(waiting);
            freeQueue(realtime);
            freeQueue(rr);
            freeList(executed);
            exit(0);
        }

        else{
            printf("Digite um numero corretamente\n");
        }
    }
    return 0;
}