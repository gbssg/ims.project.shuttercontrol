#pragma once
#include <Arduino.h>
#include "IMotor/IMotor.h"
#include <SimpleStateProcessor.h>
#include <SimpleSoftTimer.h>
#include <SparkFun_Qwiic_Relay.h>
#include "IRun/IRun.h"
#include "Scheduler/Scheduler.h"
using namespace HolisticSolutions;

typedef struct sMotorQR tMotorQR;

tMotorQR *MotorQR_create(int channelNr, tProcess *head);
void MotorQR_destroy(tMotorQR *me);

void MotorQR_init(tMotorQR *me, int channelNr, tProcess *head);
void MotorQR_deinit(tMotorQR *me);

typedef struct sChannelDescriptor
{
    uint8_t relayUp;
    uint8_t relayDown;
}tChannelDescriptor;

const tChannelDescriptor channels[] = {
    {.relayUp = 1, .relayDown = 2},
    {.relayUp = 3, .relayDown = 4}
};

typedef enum eMotorState
{
  MOTOR_ST_UNKNOWN = 0,
  MOTOR_ST_IDLE,
  MOTOR_ST_IDLEUP,
  MOTOR_ST_IDLEDOWN,
  MOTOR_ST_GOINGUP,
  MOTOR_ST_GOINGDOWN,
  MOTOR_ST_WAITUP,
  MOTOR_ST_WAITDOWN,

  MOTOR_ST_COUNT
} tMotorState;

struct sMotorQR
{
    tIMotor motor;
    uint8_t relayAddress;
    const tChannelDescriptor *channel;
    SimpleStateProcessor     *ssp;
    SimpleSoftTimer          *timer;
    Qwiic_Relay              *relay;
    tIRun                     run;
};