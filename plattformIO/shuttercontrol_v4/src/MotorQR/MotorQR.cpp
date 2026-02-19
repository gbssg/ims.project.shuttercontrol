#include "MotorQR.h"
#include <Arduino.h>
#include "NetworkServer/NetworkServer.h"

float shutterTime = 44000.0f;

void Up(tIMotor *context)
{
    tIMotor *me = context;
    me->command = UP;
}
void Down(tIMotor *context)
{
    tIMotor *me = context;
    me->command = DOWN;
}
void Stop(tIMotor *context)
{
    tIMotor *me = context;
    me->command = STOP;


}

void MotorQRHandleHeight(tMotorQR *me) {
    if (me->targetHeight != -1){
        if (me->heightPrecentage < 0) me->heightPrecentage = 0;
        if (me->heightPrecentage > 100) me->heightPrecentage = 100;
        if (me->targetHeight < 0) me->targetHeight = 0;
        if (me->targetHeight > 100) me->targetHeight = 100;
        Serial.println("Current Height: " + String(me->heightPrecentage) + " Target Height" + String(me->targetHeight));
        if(me->targetHeight < me->heightPrecentage){
            Serial.println("motor Down");
            me->motor.down(&me->motor);
        }
        else if(me->targetHeight > me->heightPrecentage){
            Serial.println("motor Up");
            me->motor.up(&me->motor);
        }
        else{
            me->motor.stop(&me->motor);
            me->targetHeight = -1;
        }
    }
}

void MotorQRRun(void *context){
    tMotorQR *me = (tMotorQR*)context;
    me->ssp->run();
    MotorQRHandleHeight(me);
}

uintptr_t MotorQRGetState(void *context){
    tMotorQR *me = (tMotorQR*)context;
    return me->ssp->CurrentStateGet();
}

const char* MotorQRGetStateName(void *context){
    tMotorQR *me = (tMotorQR*)context;
    return me->ssp->CurrentStateNameGet();
}

int MotorQRGetHeightProcentage(void *context){
    tMotorQR *me = (tMotorQR*)context;
    return me->heightPrecentage;
}

void addChangeObserver(tObserver *observerHead,tIRun *runnable, void *context){
    tObserver * current = observerHead;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (tObserver*)calloc(1, sizeof(tObserver));
    current->next->observer = runnable;
    current->next->observer->context = context;
    current->next->next = NULL;
}

void notifyAll(tObserver *observerHead){
    if (!observerHead) return;

    tObserver *current = observerHead->next;
    while (current->next != NULL)
    {
        current->observer->run(current->observer->context);
        current = current->next;
    }
    current->observer->run(current->observer->context);
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

tMotorQR *MotorQR_create(int channelNr, tProcess *processHead, tObserver *observerHead)
{
    tMotorQR *result = NULL;

    result = (tMotorQR *)calloc(1, sizeof(tMotorQR));
    if (result == NULL)
    {
        goto err_no_memory;
    }

    MotorQR_init(result, channelNr, processHead, observerHead);

    
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

void MotorQR_init(tMotorQR *me, int channelNr, tProcess *processHead, tObserver *observerHead)
{
    me->motor.up = Up;
    me->motor.down = Down;
    me->motor.stop = Stop;
    me->motor.getHightPrcentage = MotorQRGetHeightProcentage;
    me->motor.command = NONE;
    me->motor.context = me;
    me->relayAddress = 0x6D;
    me->heightPrecentage = 100;
    me->startHeight = 0;
    me->targetHeight = -1;
    me->startTime = 0;
    me->endTime = 0;
    me->relay = new Qwiic_Relay(me->relayAddress);
    if (!me->relay->begin())
    {
        Serial.print("Relay did not respond");
        while (1);
    }
    me->ssp = new SimpleStateProcessor(MOTOR_ST_UNKNOWN, MotorStateMachine, me);
    me->channel = &channels[channelNr];
    me->timer = new SimpleSoftTimer(1000);
    me->timer->start(1000);
    me->ssp->reset();
    me->ssp->run();
    
    me->run.run = MotorQRRun;
    addRunable(processHead, &me->run, me);

    me->motor.getState = MotorQRGetState;
    me->motor.getStateName = MotorQRGetStateName;

    Serial.println(me->motor.getState(me));
    Serial.println(me->motor.getStateName(me));

    me->observerHead = observerHead;
    addMotorServer(channelNr + 1, &me->motor);
}
void MotorQR_deinit(tMotorQR *me)
{
    // TODO: Find out what needs to be in the deinit
    free(me->ssp);

}

SSP_STATE_HANDLER(MotorStateUnknown)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        Serial.println("Unknown");
        motor->relay->turnAllRelaysOff();
        fsm->NextStateSet(MOTOR_ST_IDLE);
        break;
    case SSP_REASON_DO:
        /* code */
        break;
    case SSP_REASON_EXIT:
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateIdle)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
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
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateIdleUp)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        Serial.println("Motor Idle Up");
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
            if (motor->timer->isTimeout()){
                fsm->NextStateSet(MOTOR_ST_IDLE);
            }
            break;
        }
        break;
    case SSP_REASON_EXIT:
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateIdleDown)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        Serial.println("Motor Idle Down");
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
            if (motor->timer->isTimeout()){
                fsm->NextStateSet(MOTOR_ST_IDLE);
            }
            break;
        }
        break;
    case SSP_REASON_EXIT:
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateGoingUp)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        motor->startHeight = motor->heightPrecentage;
        motor->startTime = millis();
        Serial.println("Going Up");
        motor->relay->turnRelayOn(motor->channel->relayUp);
        break;
    case SSP_REASON_DO:
        motor->endTime = millis();
        if (motor->endTime - motor->startTime > 100){
            motor->heightPrecentage = motor->startHeight - ((float)(motor->endTime - motor->startTime) / shutterTime * 100);
            if(motor->heightPrecentage < 0){
                motor->heightPrecentage = 0;
                motor->startHeight = 0; //roll over prevention
            }
        }
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
        motor->relay->turnRelayOff(motor->channel->relayUp);
        motor->timer->restart();
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateGoingDown)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        motor->startTime = millis();
        motor->startHeight = motor->heightPrecentage;
        Serial.println("Going Down");
        motor->relay->turnRelayOn(motor->channel->relayDown);
        break;
    case SSP_REASON_DO:
        motor->endTime = millis();
        if (motor->endTime - motor->startTime > 100){
            motor->heightPrecentage = motor->startHeight + ((float)(motor->endTime - motor->startTime) / shutterTime * 100.0f);
            if(motor->heightPrecentage > 100){
            motor->heightPrecentage = 100;
            motor->startHeight = 100; //roll over prevention
        }
        }
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
        motor->relay->turnRelayOff(motor->channel->relayDown);
        motor->timer->restart();
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateWaitUp)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        Serial.println("Motor Wait Up");
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
            if (motor->timer->isTimeout()){
                fsm->NextStateSet(MOTOR_ST_GOINGDOWN);
            }
            break;
        }
        break;
    case SSP_REASON_EXIT:
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(MotorStateWaitDown)
{
    tIMotor *me = (tIMotor*)context;
    tMotorQR *motor = (tMotorQR*)me->context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        notifyAll(motor->observerHead);
        Serial.println("Motor Wait Down");
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
            if (motor->timer->isTimeout()){
                fsm->NextStateSet(MOTOR_ST_GOINGUP);
            }
            break;
        }
        break;
    case SSP_REASON_EXIT:
        break;
    default:
        break;
    }
    return 0;
}