#pragma once
#include "IRun/IRun.h"

typedef void (*Scheduler_Run)(void);

typedef struct sProcess tProcess;

struct  sProcess
{
    tIRun *process;
    struct sProcess *next;
};

void runAll(tProcess *head);

void addRunable(tProcess *head,tIRun *runnable, void *context);
void listRunable(tProcess *head);