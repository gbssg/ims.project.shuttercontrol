#pragma once
#include <SimpleStateProcessor.h>
#include <SimpleSoftTimer.h>
#include <SparkFun_Qwiic_Button.h>
#include "IMotor/IMotor.h"
#include "IRun/IRun.h"
#include "Scheduler/Scheduler.h"
using namespace HolisticSolutions;

typedef struct sControl tControl;

typedef struct sButtonDescriptor
{
    uint8_t      addrUp;
    uint8_t      addrDown;
}tButtonDescriptor;

const tButtonDescriptor buttons[] = {
    {.addrUp = 0x6F, .addrDown = 0x71},
    {.addrUp = 0x72, .addrDown = 0x73}
};


tControl *Control_create(uint8_t buttonGrpNr, tIMotor *motor, tProcess *head);
void Control_destroy(tControl *me);

void Control_init(tControl *me, uint8_t buttonGrpNr, tIMotor *motor, tProcess *head);
void Control_deinit(tControl *me);

// typedef void (* tControl_GetState)(tControl *me);
typedef void (* tControl_Setup)(tControl * me);

typedef enum eControlState
{
  CONTROL_ST_UNKNOWN = 0,
  CONTROL_ST_IDLE,
  CONTROL_ST_GOINGUP,
  CONTROL_ST_GOINGDOWN,

  CONTROL_ST_COUNT
} tControlState;

struct sControl
{
    SimpleStateProcessor    *ssp;
    const tButtonDescriptor *button;
    // TODO: is the setup needed or should i just make it in init? or call it in init
    tControl_Setup           setup;
    QwiicButton             *buttonUp;
    QwiicButton             *buttonDown;
    tIMotor                 *motor;
    SimpleSoftTimer         *timerPressed;
    tIRun                    run;
    // TODO: Add state return function
    // tControl_GetState getState;
};