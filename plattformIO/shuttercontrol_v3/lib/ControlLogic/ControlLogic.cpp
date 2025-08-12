#include <SimpleStateProcessor.h>
#include <SimpleSoftTimer.h>
#include <HardwareSetup.h>
#include <GlobalVariables.h>
#include <MotorLogic.h>
using namespace HolisticSolutions;

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

SSP_STATE_HANDLER(ControlStateUnknown)
{
if (reason == SSP_REASON_ENTER)
{
    fsm->NextStateSet(CONTROL_ST_IDLE);
    Serial.println("Unknown");
    buttonUp1.LEDon();
    buttonDown1.LEDon();
}
if (reason == SSP_REASON_DO)
{
    Serial.print("Error didnt exit state Unknown cleanly");
}
return 0;
}

SSP_STATE_HANDLER(ControlStateIdle)
{
if (reason == SSP_REASON_ENTER)
{
    _controlmotor = CONTROLMOTOR_STOP;
    Serial.println("Idle");
    buttonUp1.LEDoff();
    buttonDown1.LEDoff();
}
if (reason == SSP_REASON_DO)
{
    if (buttonUp1.isPressed() && _timerPressed.isTimeout())
    {
    _timerPressed.restart();
    fsm->NextStateSet(CONTROL_ST_GOINGUP);
    }
    if (buttonDown1.isPressed() && _timerPressed.isTimeout())
    {
    _timerPressed.restart();
    fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
    }
}
return 0;
}

SSP_STATE_HANDLER(ControlStateGoingUp)
{
if (reason == SSP_REASON_ENTER)
{
    _controlmotor = CONTROLMOTOR_UP;
    Serial.println("GoUp");
    buttonUp1.LEDon();
    buttonDown1.LEDoff();
}
if (reason == SSP_REASON_DO)
{
    if (buttonUp1.isPressed() && _timerPressed.isTimeout())
    {
    _timerPressed.restart();
    fsm->NextStateSet(CONTROL_ST_IDLE);
    }
    if (buttonDown1.isPressed() && _timerPressed.isTimeout())
    {
    _timerPressed.restart();
    fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
    }
}
return 0;
}

SSP_STATE_HANDLER(ControlStateGoingDown)
{
if (reason == SSP_REASON_ENTER)
{
    _controlmotor = CONTROLMOTOR_DOWN;
    Serial.println("GoDown");
    buttonUp1.LEDoff();
    buttonDown1.LEDon();
}
if (reason == SSP_REASON_DO)
{
    if (buttonUp1.isPressed() && _timerPressed.isTimeout())
    {
    _timerPressed.restart();
    fsm->NextStateSet(CONTROL_ST_GOINGUP);
    }
    if (buttonDown1.isPressed() && _timerPressed.isTimeout())
    {
    _timerPressed.restart();
    fsm->NextStateSet(CONTROL_ST_IDLE);
    }
}
return 0;
}

void setupControl()
{
    Control.reset();
}

void testingControl()
{
    Control.run();
}

void runControl()
{
    Control.run();
}
