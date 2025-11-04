#pragma once

#include <Arduino.h>
#include <SimpleStateProcessor.h>
#include "MotroInterface.h"


// void GoUp();
// void GoDown();
// void Stop();
// uintptr_t getState();


static void setupMotor(tMotor * motor, int channel);
static void Up();
static void Down();
static void Stop();

extern tMotorStrategy MotorQR;