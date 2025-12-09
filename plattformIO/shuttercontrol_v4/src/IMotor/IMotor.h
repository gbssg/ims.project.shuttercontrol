#pragma once

#include <Arduino.h>

typedef struct sIMotor tIMotor;

typedef void (* tIMotor_Dir)(void *context);
typedef uintptr_t (* tIMotor_GetState)(void *context);
typedef const char * (* tIMotor_GetStateName)(void *context);

struct sIMotor
{
    tIMotor_Dir          up;
    tIMotor_Dir          down;
    tIMotor_Dir          stop;
    // TODO: Add state return function and Implementation in all Classes (is get State Needed as Name or number?)
    tIMotor_GetState     getState;
    tIMotor_GetStateName getStateName;
};
