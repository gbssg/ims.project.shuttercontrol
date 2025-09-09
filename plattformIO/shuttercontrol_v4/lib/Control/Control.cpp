#include "Control.h"

SSP_STATE_HANDLER(ControlStateUnknown);
SSP_STATE_HANDLER(ControlStateStop);
SSP_STATE_HANDLER(ControlStateUp);
SSP_STATE_HANDLER(ControlStateDown);

static const tSSP_State ControlStateMachine[] = {
    SSP_STATE_DESCRIBE("Unknown", ControlStateUnknown),
    SSP_STATE_DESCRIBE("Stop", ControlStateStop),
    SSP_STATE_DESCRIBE("Up", ControlStateUp),
    SSP_STATE_DESCRIBE("Down", ControlStateDown),

    SSP_STATE_LAST()};


void tControl::run()
{
    sspControl ->run();
}

void tControl::setup()
{
    buttonUp = new QwiicButton();
    buttonUp->begin(this -> buttonUpAddr);
    buttonDown = new QwiicButton();
    buttonDown->begin(this -> buttonUpAddr);
    sspControl = new SimpleStateProcessor(CONTROL_ST_UNKNOWN, ControlStateMachine, 0);
    sspControl -> reset();
}

uintptr_t tControl::getState()
{
    return sspControl ->CurrentStateGet();
}

tControl* control1 = new tControl();
tControl* control2 = new tControl();

SSP_STATE_HANDLER(ControlStateUnknown)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        fsm-> NextStateSet(CONTROL_ST_IDLE);
        Serial.println("Unknown");
        buttonUp->LEDon();
        buttonDown->LEDon();
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

SSP_STATE_HANDLER(ControlStateStop)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        fsm-> NextStateSet(CONTROL_ST_IDLE);
        Serial.println("Unknown");

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

SSP_STATE_HANDLER(ControlStateUp)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        fsm-> NextStateSet(CONTROL_ST_IDLE);
        Serial.println("Unknown");

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

SSP_STATE_HANDLER(ControlStateDown)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        fsm-> NextStateSet(CONTROL_ST_IDLE);
        Serial.println("Unknown");

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