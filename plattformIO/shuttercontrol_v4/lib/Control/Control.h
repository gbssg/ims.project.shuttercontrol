#pragma once

#include <Motor.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleStateProcessor.h>

// enum for control ssp
typedef enum eControlState
{
  CONTROL_ST_UNKNOWN = 0,
  CONTROL_ST_IDLE,
  CONTROL_ST_GOINGUP,
  CONTROL_ST_GOINGDOWN,

  CONTROL_ST_COUNT
} tControlState;

// struct for the button addresses
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
    SimpleStateProcessor * ssp;
    tMotor * motor;
    const tAddressDescriptor * desc;
    tButton * button;
}tControl;

extern const tSSP_State ControlStateMachine[];

void setupControl(tControl * me, tMotor * motor, int addressNr, tButton * button);