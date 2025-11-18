#include "MotorQR.h"
#include <Arduino.h>

void Up(tIMotor *me)
{
}
void Down(tIMotor *me)
{
}
void Stop(tIMotor *me)
{
}

SSP_STATE_HANDLER(MotorStateUnknown);
SSP_STATE_HANDLER(MotorStateIdle);
SSP_STATE_HANDLER(MotorStateIdleUp);
SSP_STATE_HANDLER(MotorStateIdleDown);
SSP_STATE_HANDLER(MotorStateGoingUp);
SSP_STATE_HANDLER(MotorStateGoingDown);
SSP_STATE_HANDLER(MotorStateWaitUp);
SSP_STATE_HANDLER(MotorStateWaitDown);

static const tSSP_State MotorStateMachine[] = {
    SSP_STATE_DESCRIBE("Unknown", MotorStateUnknown),
    SSP_STATE_DESCRIBE("Idle", MotorStateIdle),
    SSP_STATE_DESCRIBE("IdleUp", MotorStateIdleUp),
    SSP_STATE_DESCRIBE("IdleDown", MotorStateIdleDown),
    SSP_STATE_DESCRIBE("goingUp", MotorStateGoingUp),
    SSP_STATE_DESCRIBE("goingDown", MotorStateGoingDown),
    SSP_STATE_DESCRIBE("WaitingUp", MotorStateWaitUp),
    SSP_STATE_DESCRIBE("WaitingDown", MotorStateWaitDown),

    SSP_STATE_LAST()};

tMotorQR *MotorQR_create(int channelNr)
{
    tMotorQR *result = NULL;

    result = (tMotorQR *)calloc(1, sizeof(tMotorQR));
    if (result == NULL)
    {
        goto err_no_memory;
    }

    MotorQR_init(result, channelNr);

    return result;

    free(result);
    result = NULL;

err_no_memory:
    return result;
}
void MotorQR_destroy(tMotorQR *me)
{
    if (me != NULL)
    {
        free(me);
        me = NULL;
    }
}

void MotorQR_init(tMotorQR *me, int channelNr)
{
    me->motor.up = Up;
    me->motor.down = Down;
    me->motor.stop = Stop;
    // TODO: Add the context to the Processor
    me->ssp = new SimpleStateProcessor(MOTOR_ST_UNKNOWN, MotorStateMachine, 0);
    me->channel = &channels[channelNr];
    me->timer = new SimpleSoftTimer(1000);
    me->timer->start(1000);
    me->ssp->reset();
    me->ssp->run();
    me->ssp->NextStateSet(MOTOR_ST_GOINGUP);
    me->ssp->run();
    Serial.print(me->ssp->CurrentStateNameGet());
}
void MotorQR_deinit(tMotorQR *me)
{
    // TODO: Find out what needs to be in the deinit
}

// TODO: Implement the Simple State Processor

SSP_STATE_HANDLER(MotorStateUnknown)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateIdle)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateIdleUp)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateIdleDown)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateGoingUp)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateGoingDown)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateWaitUp)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateWaitDown)
{
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}