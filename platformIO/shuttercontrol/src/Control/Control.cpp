#include <Arduino.h>
#include "Control.h"
#include "MotorQR/MotorQR.h"


const int cmdDuration = 300;
const uint8_t brightness = 100;
unsigned long holdTimeout = 300;

void ControlRun(void *context){
    tControl *me = (tControl*)context;
    me->ssp->run();
}

void Setup(tControl *me){

}

void motorNotification(void *context){
    tControl *me = (tControl*)context;
    Serial.println("Control was Notified");
    me->currentMotorState = me->motor->getState(me->motor);
    Serial.print("Current State is: ");
    Serial.println(me->currentMotorState);
    if(me->currentMotorState == MOTOR_ST_GOINGUP){
        me->buttonUp->LEDon(brightness);
    }
    else{
        me->buttonUp->LEDoff();
    }
    if(me->currentMotorState == MOTOR_ST_GOINGDOWN){
        me->buttonDown->LEDon(brightness);
    }
    else{
        me->buttonDown->LEDoff();
    }
}

int checkButton(QwiicButton* button, tControl *me){

    if (!me->isPressed && button->isPressed())
    {
        me->isPressed = true;
        me->holdTriggered = false;
        me->buttonTimestamp = millis();
 
        button->clearEventBits();
        return 0;
    }
 
    if (me->isPressed && button->isPressed())
    {
        if (!me->holdTriggered && (millis() - me->buttonTimestamp) >= holdTimeout)
        {
            me->holdTriggered = true;
            return 2;
        }
        return 0;
    }
 
    if (me->isPressed && !button->isPressed() && button->hasBeenClicked())
    {
        me->isPressed = false;
        button->clearEventBits();
 
        if (!me->holdTriggered) {
            return 1;
        }
    }
 
    return 0;
}

void runControl(void *context){
    tControl *me = (tControl*)context;
    switch (checkButton(me->buttonUp, me))
    {
    case 1:
        if(me->currentMotorState == MOTOR_ST_GOINGUP){
            me->motor->stop(me->motor);
        }
        else{
            me->motor->up(me->motor);
            me->checkTimeout = true;
            me->timerShortPress->restart();
        }  
        break;
    case 2:
        if(me->currentMotorState == MOTOR_ST_GOINGUP){
            me->motor->stop(me->motor);
        }
        else{
            me->motor->up(me->motor);
        }
        break;
    default:
        break;
    }

    switch (checkButton(me->buttonDown, me))
    {
    case 1:
        if(me->currentMotorState == MOTOR_ST_GOINGDOWN){
            me->motor->stop(me->motor);
        }
        else{
            me->motor->down(me->motor);
            me->checkTimeout = true;
            me->timerShortPress->restart();
        }
        break;
    case 2:
        if(me->currentMotorState == MOTOR_ST_GOINGDOWN){
            me->motor->stop(me->motor);
        }
        else{
            me->motor->down(me->motor);
        }
        break;
    default:
        break;
    }

    if (me->timerShortPress->isTimeout() && me->checkTimeout)
    {
        me->motor->stop(me->motor);
        me->checkTimeout = false;
    }

}

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

tControl *Control_create(uint8_t buttonGrpNr, tIMotor *motor, tProcess *head, tObserver *observerHead){
    tControl *result = NULL;

    result = (tControl *)calloc(1, sizeof(tControl));
    if (result == NULL)
    {
        goto err_no_memory;
    }

    Control_init(result, buttonGrpNr, motor, head, observerHead);

    return result;

    free(result);
    result = NULL;

err_no_memory:
    Serial.print("Error no Memory");
    return result;
}
void Control_destroy(tControl *me){
    if (me != NULL)
    {
        free(me);
        me = NULL;
    }
}


void Control_init(tControl *me, uint8_t buttonGrpNr, tIMotor *motor, tProcess *head, tObserver *observerHead){
    me->button = &buttons[buttonGrpNr];
    me->setup = Setup;
    me->buttonUp = new QwiicButton();
    me->buttonDown = new QwiicButton();
    if (!me->buttonUp->begin(me->button->addrUp))
    {
        Serial.printf("Button at address 0x%X did not Respond Freezing\n", me->button->addrUp);
        while (1);
    }
    if (!me->buttonDown->begin(me->button->addrDown))
    {
        Serial.printf("Button at address 0x%X did not Respond Freezing\n", me->button->addrUp);
        while (1);
    }
    me->buttonUp->enableClickedInterrupt();
    me->buttonDown->enableClickedInterrupt();
    me->buttonUp->enablePressedInterrupt();
    me->buttonDown->enablePressedInterrupt();
    me->buttonUp->LEDoff();
    me->buttonDown->LEDoff();
    me->timerShortPress = new SimpleSoftTimer(cmdDuration);
    me->timerShortPress->start(cmdDuration);
    me->timerShortPress->restart();
    // Chech button clears Queue
    checkButton(me->buttonUp, me);
    checkButton(me->buttonDown, me);
    me->motor = motor;
    me->run.run = runControl;
    addRunable(head, &me->run, me);
    me->notification.run = motorNotification;
    addChangeObserver(observerHead, &me->notification, me);
}

void Control_deinit(tControl *me){

}