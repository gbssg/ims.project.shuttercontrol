#pragma once

typedef struct sIMotor tIMotor;

typedef void (* tIMotor_Dir)(tIMotor *me);

struct sIMotor
{
    tIMotor_Dir up;
    tIMotor_Dir down;
    tIMotor_Dir stop;
    // TODO: Add state return function
};
