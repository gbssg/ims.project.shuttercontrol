#pragma once
#include <SimpleStateProcessor.h>

typedef struct sControl tControl;

typedef struct sButtonDescriptor
{
    uint8_t addrUp;
    uint8_t addrDown;
}tButtonDescriptor;

const tButtonDescriptor buttons[] = {
    {.addrUp = 0x6F, .addrDown = 0x71},
    {.addrUp = 0x72, .addrDown = 0x73}
};


tControl *Control_create(SimpleStateProcessor *ssp, uint8_t buttonGrpNr);
void Control_destroy(tControl *me);

void Control_init(tControl *me);
void Control_deinit(tControl *me);

// typedef void (* tControl_GetState)(tControl *me);
typedef void (* tControl_Setup)(tControl * me);
typedef int (* tControl_Run)(tControl * me);

typedef enum eControlState
{
  CONTROL_ST_UNKNOWN = 0,
  CONTROL_ST_IDLE,
  CONTROL_ST_GOINGUP,
  CONTROL_ST_GOINGDOWN,

  CONTROL_ST_COUNT
} tControlState;