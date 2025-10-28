#pragma once

#include <Arduino.h>


// void GoUp();
// void GoDown();
// void Stop();
// uintptr_t getState();

typedef struct sChannelDescriptor
{
    int pinR1;
    int pinR2;
}tChannelDescriptor;

typedef struct sSSP_Motor
{

}tSSP_Motor;

typedef struct sMotor
{
    tSSP_Motor * ssp;
    const tChannelDescriptor * desc;
}tMotor;


void Motor(tMotor * motor, int channel);