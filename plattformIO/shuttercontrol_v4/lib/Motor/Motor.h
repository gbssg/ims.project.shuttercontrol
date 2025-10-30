#pragma once

#include <Arduino.h>
#include <SimpleStateProcessor.h>


// void GoUp();
// void GoDown();
// void Stop();
// uintptr_t getState();

typedef struct sChannelDescriptor
{
    int pinR1;
    int pinR2;
}tChannelDescriptor;

typedef struct sMotor
{
    SimpleStateProcessor * ssp;
    const tChannelDescriptor * desc;
}tMotor;


void Motor(tMotor * motor, int channel);