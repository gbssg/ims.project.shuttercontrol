#pragma once

#include <Arduino.h>
#include <SimpleStateProcessor.h>

typedef struct sControl
{
    void setup();
    void run();
    uintptr_t getState();
    SimpleStateProcessor* sspControl;
}tControl;


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
