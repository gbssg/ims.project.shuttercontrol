#pragma once

#include <Arduino.h>

typedef struct sIMotor tIMotor;

enum eCommand{
    NONE,
    UP,
    DOWN1,
    DOWN2,
    STOP
};

typedef enum eCommand tCommand;

typedef void (* tIMotor_Dir)(tIMotor *context);
typedef uintptr_t (* tIMotor_GetState)(void *context);
typedef const char * (* tIMotor_GetStateName)(void *context);

struct sIMotor
{
    tIMotor_Dir          up;
    tIMotor_Dir          down1;
    tIMotor_Dir          down2;
    tIMotor_Dir          stop;
    tIMotor_GetState     getState;
    tIMotor_GetStateName getStateName;
    eCommand command;
    void *context;
};
