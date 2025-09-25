#pragma once

#include <Arduino.h>
#include <SimpleStateProcessor.h>
#include <SparkFun_Qwiic_Button.h>

typedef struct sControl
{
    void setup(const tControl* control);
    void run();
    uintptr_t getState();
    uint8_t buttonUpAddr;
    uint8_t buttonDownAddr;
    SimpleStateProcessor* sspControl;
    QwiicButton* buttonUp;
    QwiicButton* buttonDown;
}tControl;

const tControl controls[] = {
    {.buttonUpAddr = 0x70, .buttonDownAddr = 0x71},
    {.buttonUpAddr = 0x73, .buttonDownAddr = 0x74}
};

typedef enum eControlState
{
  CONTROL_ST_UNKNOWN = 0,
  CONTROL_ST_IDLE,
  CONTROL_ST_GOINGUP,
  CONTROL_ST_GOINGDOWN,

  CONTROL_ST_COUNT
} tControlState;

extern tControl* control1;
extern tControl* control2;

extern QwiicButton* buttonUp;
extern QwiicButton* buttonDown;
