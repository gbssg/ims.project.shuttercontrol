#pragma once

#include <Motor.h>
#include <SparkFun_Qwiic_Button.h>

typedef struct sAddressDescriptor
{
    uint8_t addrB1;
    uint8_t addrB2;
}tAddressDescriptor;

typedef struct sSSP_Control
{
    
}tSSP_Control;

typedef struct sButton
{
    QwiicButton * up;
    QwiicButton * down;
}tButton;

typedef struct sControl
{
    tSSP_Control * ssp;
    tMotor * motor;
    const tAddressDescriptor * desc;
    tButton * button;
}tControl;

void setupControl(tControl * me, tMotor * motor, int addressNr, QwiicButton buttonUp, QwiicButton buttonDown);