#pragma once

typedef struct sChannelDescriptor
{
    int pinR1;
    int pinR2;
}tChannelDescriptor;

typedef struct sMotor tMotor;

typedef struct sMotorStrategy
{
    void (*up)(void);
    void (*down)(void);
    void (*stop)(void);
    void (*setup)(tMotor * me, int channel);
}tMotorStrategy;

typedef struct sMotor
{
    SimpleStateProcessor * ssp;
    const tChannelDescriptor * desc;
    tMotorStrategy * strategy;
}tMotor;