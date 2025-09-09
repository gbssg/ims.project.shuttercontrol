#pragma once

#include <Arduino.h>
#include <SimpleSoftTimer.h>
using namespace HolisticSolutions;

typedef struct sMotor 
{
    void setup();
    void up();
    void down();
    void stop();
    void run();
    uintptr_t getState();
    SimpleSoftTimer* sstTimeout;
}tMotor;