
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

void tControl::setup(const tControl* control)
{
    buttonUp = new QwiicButton();
    buttonUp->begin(control -> buttonDownAddr);
    buttonDown = new QwiicButton();
    buttonDown->begin(control -> buttonUpAddr);
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
        buttonUp->LEDoff();
        buttonDown->LEDoff();
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
        Serial.println("Stop");
        break;
    case SSP_REASON_DO:
        if (buttonUp->isPressed())
        {fsm->NextStateSet(CONTROL_ST_GOINGUP);}
        if (buttonDown->isPressed())
        {fsm->NextStateSet(CONTROL_ST_GOINGDOWN);}
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
        Serial.println("Up");
        break;
    case SSP_REASON_DO:
        if (buttonUp->isPressed())
        {fsm->NextStateSet(CONTROL_ST_IDLE);}
        if (buttonDown->isPressed())
        {fsm->NextStateSet(CONTROL_ST_GOINGDOWN);}
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
        Serial.println("Down");
        break;
    case SSP_REASON_DO:
        if (buttonUp->isPressed())
        {fsm->NextStateSet(CONTROL_ST_GOINGUP);}
        if (buttonDown->isPressed())
        {fsm->NextStateSet(CONTROL_ST_IDLE);}
        break;
    case SSP_REASON_EXIT:
        break;
    default:
        break;
    }
    return 0;
}