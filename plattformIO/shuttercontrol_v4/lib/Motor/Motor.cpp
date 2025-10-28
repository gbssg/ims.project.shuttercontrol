#include "Motor.h"

// void GoUp(){}
// void GoDown(){}
// void Stop(){}
// uintptr_t getState(){}

const tChannelDescriptor channels[] = {
    {.pinR1 = 1, .pinR2 = 2},
    {.pinR1 = 3, .pinR2 = 4}
};

void Motor(tMotor * me, int channel)
{
    me->desc = &channels[channel];
}
