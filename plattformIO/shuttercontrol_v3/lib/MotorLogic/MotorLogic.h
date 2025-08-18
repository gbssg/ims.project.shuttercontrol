// Simple State Processor controlling the Relais for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#pragma once
#include <Arduino.h>
void setupMotor();
void runMotor();
uintptr_t getMotorState();