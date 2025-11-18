#pragma once

typedef struct sIRun tIRun;

// TODO: What do I do to make it able to take different objects as "me" / context
// Should i use a void pointer
typedef void (* tIRun_Run)(tIRun *me);

struct sIRun
{
    tIRun_Run run;
};
