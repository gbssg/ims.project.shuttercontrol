#include "Motor.h"

// void GoUp(){}
// void GoDown(){}
// void Stop(){}
// uintptr_t getState(){}

const tChannelDescriptor channels[] = {
    {.pinR1 = 1, .pinR2 = 2},
    {.pinR1 = 3, .pinR2 = 4}
};

static void setupMotor(tMotor * me, int channel)
{
    me->desc = &channels[channel];
}

static void Up()
{
    Serial.println("MotorSt1 Up");
}

static void Down()
{
    Serial.println("MotorSt1 Down");
}

static void Stop()
{
    Serial.println("MotorSt1 Down");
}

tMotorStrategy MotorQR = {
    .up = Up,
    .down = Down,
    .stop = Stop,
    .setup = setupMotor
};