#include "Scheduler.h"
#include <Arduino.h>

//TODO: Make a list for the runables

void addRunable(tProcess *head,tIRun *runnable, void *context){
    tProcess * current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (tProcess*)calloc(1, sizeof(tProcess));
    current->next->process = runnable;
    current->next->process->context = context;
    current->next->next = NULL;
}

void addRunnableStart(tProcess *head,tIRun *runnable, void *context){
    tProcess *node = (tProcess*)calloc(1, sizeof(tProcess));
    node->next = head->next;
    head->next = node;
    head->next->process = runnable;
    head->next->process->context = context;
}

void listRunable(){
}

void runAll(tProcess *head){
    tProcess *current = head->next;
    while (current->next != NULL)
    {
        current->process->run(current->process->context);
        current = current->next;
    }
    current->process->run(current->process->context);
}