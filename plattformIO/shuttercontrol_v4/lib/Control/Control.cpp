#include "Control.h"
#include <SimpleStateProcessor.h>

const sAddressDescriptor address[] = {
    {.addrB1 = 0x6F, .addrB2 = 0x71},
    {.addrB1 = 0x72, .addrB2 = 0x73},
};

SSP_STATE_HANDLER(ControlStateUnknown);
SSP_STATE_HANDLER(ControlStateIdle);
SSP_STATE_HANDLER(ControlStateGoingUp);
SSP_STATE_HANDLER(ControlStateGoingDown);

const tSSP_State ControlStateMachine[] = {
    SSP_STATE_DESCRIBE("Unknown", ControlStateUnknown),
    SSP_STATE_DESCRIBE("Idle", ControlStateIdle),
    SSP_STATE_DESCRIBE("goingUp", ControlStateGoingUp),
    SSP_STATE_DESCRIBE("goingDown", ControlStateGoingDown),

    SSP_STATE_LAST()};

void setupControl(tControl *me, tMotor *motor, int addressNr, tButton *button)
{
    me->desc = &address[addressNr];
    me->button = button;
    if (!me->button->up->begin(me->desc->addrB1))
    {
        Serial.println(me->desc->addrB1);
        Serial.println("connection Failed");
    }
    if (!me->button->down->begin(me->desc->addrB2))
    {
        Serial.println(me->desc->addrB2);
        Serial.println("connection Failed");
    }
}

SSP_STATE_HANDLER(ControlStateUnknown)
{
    tControl *me = (tControl *)(context);
    switch (reason)
    {
    case SSP_REASON_ENTER:
        me->button->up->LEDoff();
        me->button->down->LEDoff();
        break;
    case SSP_REASON_DO:
        break;
    case SSP_REASON_EXIT:
        Serial.println("Exit");
        break;
    default:
        break;
    }
    return 0;
}
SSP_STATE_HANDLER(ControlStateIdle)
{
    tControl *me = (tControl *)(context);
    switch (reason)
    {
    case SSP_REASON_ENTER:
        break;
    case SSP_REASON_DO:

        break;
    case SSP_REASON_EXIT:

        break;
    default:
        break;
    }
    return 0;
}
SSP_STATE_HANDLER(ControlStateGoingUp)
{
    tControl *me = (tControl *)(context);
    switch (reason)
    {
    case SSP_REASON_ENTER:

        break;
    case SSP_REASON_DO:

        break;
    case SSP_REASON_EXIT:

        break;
    default:
        break;
    }
    return 0;
}
SSP_STATE_HANDLER(ControlStateGoingDown)
{
    tControl *me = (tControl *)(context);
    switch (reason)
    {
    case SSP_REASON_ENTER:

        break;
    case SSP_REASON_DO:

        break;
    case SSP_REASON_EXIT:

        break;
    default:
        break;
    }
    return 0;
}
