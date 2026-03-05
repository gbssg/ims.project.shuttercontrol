#pragma once

#include <Arduino.h>

typedef struct sIMotor tIMotor;

enum eCommand{
    NONE,
    UP,
    DOWN,
    STOP
};

typedef enum eCommand tCommand;

typedef void (* tIMotor_Dir)(tIMotor *context);
typedef void (* tIMotor_Update)(tIMotor *context);
typedef uintptr_t (* tIMotor_GetState)(void *context);
typedef const char * (* tIMotor_GetStateName)(void *context);

struct sIMotor
{
    tIMotor_Dir          up;
    tIMotor_Dir          down;
    tIMotor_Dir          stop;
    tIMotor_GetState     getState;
    tIMotor_GetStateName getStateName;
    eCommand             command;
    tIMotor_Update       update;
    int                  time;
    int                  startTime;
    void                *context;
};
