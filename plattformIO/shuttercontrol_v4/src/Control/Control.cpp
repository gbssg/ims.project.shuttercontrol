#include "Control.h"
#include <Arduino.h>

struct sControl
{
    SimpleStateProcessor *ssp;
    tButtonDescriptor *buttons;
    // TODO: Ask if this needs to be a pointer
    // tControl_GetState getState;
    // TODO: is the setup needed or should i just make it in init?
    tControl_Setup setup;
    tControl_Run run;
    // TODO: Add state return function
};

SSP_STATE_HANDLER(ControlStateUnknown);
SSP_STATE_HANDLER(ControlStateIdle);
SSP_STATE_HANDLER(ControlStateGoingUp);
SSP_STATE_HANDLER(ControlStateGoingDown);

static const tSSP_State ControlStateMachine[] = {
    SSP_STATE_DESCRIBE("Unknown", ControlStateUnknown),
    SSP_STATE_DESCRIBE("Idle", ControlStateIdle),
    SSP_STATE_DESCRIBE("goingUp", ControlStateGoingUp),
    SSP_STATE_DESCRIBE("goingDown", ControlStateGoingDown),

    SSP_STATE_LAST()};

tControl *Control_create(uint8_t buttonGrpNr)
{
    tControl *result = NULL;

    result = (tControl *)calloc(1, sizeof(tControl));
    if (result == NULL)
    {
        goto err_no_memory;
    }

    Control_init(result, buttonGrpNr);

    return result;

    free(result);
    result = NULL;

err_no_memory:
    return result;
}
void Control_destroy(tControl *me)
{
    if (me != NULL)
    {
        free(me);
        me = NULL;
    }
}

void Control_init(tControl *me, uint8_t buttonGrpNr)
{
    me->ssp = new SimpleStateProcessor(CONTROL_ST_UNKNOWN, ControlStateMachine, 0);
    buttons[buttonGrpNr];
}
void Control_deinit(tControl *me)
{
    // TODO: Find out what needs to be in the deinit
}