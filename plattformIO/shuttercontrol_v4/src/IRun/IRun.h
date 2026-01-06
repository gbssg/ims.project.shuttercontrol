#pragma once

typedef struct sIRun tIRun;

typedef void (* tIRun_Run)(void *context);

struct sIRun
{
    tIRun_Run run;
    void *context;
};
