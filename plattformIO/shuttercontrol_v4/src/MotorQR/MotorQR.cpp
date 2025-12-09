#include "MotorQR.h"
#include <Arduino.h>

void Up(void *context)
{
    tMotorQR *me = (tMotorQR*)context;
    me->command = UP;
}
void Down(void *context)
{
    tMotorQR *me = (tMotorQR*)context;
    me->command = DOWN;
}
void Stop(void *context)
{
    tMotorQR *me = (tMotorQR*)context;
    me->command = STOP;
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
    MotorQR_deinit(me);
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
    me->command = NONE;
    // TODO: Add the context to the Processor
    me->ssp = new SimpleStateProcessor(MOTOR_ST_UNKNOWN, MotorStateMachine, me);
    me->channel = &channels[channelNr];
    me->timer = new SimpleSoftTimer(1000);
    me->timer->start(1000);
    me->ssp->reset();
    me->ssp->run();
    // SSP Test Code
    // me->ssp->NextStateSet(MOTOR_ST_GOINGUP);
    // me->ssp->run();
    // Serial.print(me->ssp->CurrentStateNameGet());
}
void MotorQR_deinit(tMotorQR *me)
{
    // TODO: Find out what needs to be in the deinit
    free(me->ssp);

}

// TODO: Implement the Simple State Processor

SSP_STATE_HANDLER(MotorStateUnknown)
{
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Unknown");
        fsm->NextStateSet(MOTOR_ST_IDLE);
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Motor Idle");
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            fsm->NextStateSet(MOTOR_ST_GOINGUP);
            me->command = NONE;
            break;
        case DOWN:
            fsm->NextStateSet(MOTOR_ST_GOINGDOWN);
            me->command = NONE;
            break;
        case STOP:
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            fsm->NextStateSet(MOTOR_ST_WAITDOWN);
            me->command = NONE;
            break;
        case DOWN:
            fsm->NextStateSet(MOTOR_ST_GOINGDOWN);
            me->command = NONE;
            break;
        case STOP:
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            fsm->NextStateSet(MOTOR_ST_GOINGUP);
            me->command = NONE;
            break;
        case DOWN:
            fsm->NextStateSet(MOTOR_ST_WAITUP);
            me->command = NONE;
            break;
        case STOP:
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Going Up");
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            me->command = NONE;
            break;
        case DOWN:
            fsm->NextStateSet(MOTOR_ST_WAITUP);
            me->command = NONE;
            break;
        case STOP:
        fsm->NextStateSet(MOTOR_ST_IDLEDOWN);
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Going Down");
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            fsm->NextStateSet(MOTOR_ST_WAITDOWN);
            me->command = NONE;
            break;
        case DOWN:
            me->command = NONE;
            break;
        case STOP:
            fsm->NextStateSet(MOTOR_ST_IDLEUP);
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            me->command = NONE;
            break;
        case DOWN:
            me->command = NONE;
            break;
        case STOP:
            fsm->NextStateSet(MOTOR_ST_IDLEDOWN);
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
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
    tMotorQR *me = (tMotorQR*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        /* code */
        break;
    case SSP_REASON_DO:
        switch (me->command)
        {
        case UP:
            me->command = NONE;
            break;
        case DOWN:
            me->command = NONE;
            break;
        case STOP:
            fsm->NextStateSet(MOTOR_ST_IDLEUP);
            me->command = NONE;
            break;
        default:
            me->command = NONE;
            break;
        }
        break;
    case SSP_REASON_EXIT:
        /* code */
        break;
    default:
        break;
    }
    return 0;
}