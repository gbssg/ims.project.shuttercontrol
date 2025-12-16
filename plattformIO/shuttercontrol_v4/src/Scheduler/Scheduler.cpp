#include "Scheduler.h"
#include <Arduino.h>

//TODO: Make a list for the runables

void addRunable(tProcess *head,tIRun *runnable){
    tProcess * current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (tProcess*)calloc(1, sizeof(tProcess));
    current->next->process = runnable;
    current->next->next = NULL;
}

void listRunable(){
}

void runAll(tProcess *head){
    tProcess *current = head->next;
    while (current->next != NULL)
    {
        current->process->run(current->process);
        current = current->next;
    }
    current->process->run(current->process);
}