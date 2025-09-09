#include "Control.h"

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


static SimpleStateProcessor Control(CONTROL_ST_UNKNOWN, ControlStateMachine, 0);


void tControl::run()
{
    Serial.println("Hello World");
}

void tControl::setup()
{

}

void tControl::getState()
{
    
}

tControl* control1 = new tControl();
tControl* control2 = new tControl();