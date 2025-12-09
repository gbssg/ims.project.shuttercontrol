#pragma once
#include <SimpleStateProcessor.h>
#include <SparkFun_Qwiic_Button.h>
#include "IMotor/IMotor.h"

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


tControl *Control_create(uint8_t buttonGrpNr, tIMotor *motor);
void Control_destroy(tControl *me);

void Control_init(tControl *me, uint8_t buttonGrpNr);
void Control_deinit(tControl *me);

// typedef void (* tControl_GetState)(tControl *me);
typedef void (* tControl_Setup)(tControl * me);
typedef void (* tControl_Run)(tControl * me);

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
    tControl_Run             run;
    QwiicButton             *buttonUp;
    QwiicButton             *buttonDown;
    tIMotor                 *motor;
    // TODO: Add state return function
    // tControl_GetState getState;
};