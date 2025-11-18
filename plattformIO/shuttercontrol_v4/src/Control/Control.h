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


tControl *Control_create();
void Control_destroy(tControl *me);

void Control_init(tControl *me);
void Control_deinit(tControl *me);

// typedef void (* tControl_GetState)(tControl *me);
typedef void (* tControl_Setup)(tControl * me);
typedef void (* tControl_Run)(tControl * me);



struct sControl
{
    SimpleStateProcessor ssp;
    uint8_t buttonGroup;
    // TODO: Ask if this needs to be a pointer
    // tControl_GetState getState;
    tControl_Setup setup;
    tControl_Run run;
    // TODO: Add state return function
};
