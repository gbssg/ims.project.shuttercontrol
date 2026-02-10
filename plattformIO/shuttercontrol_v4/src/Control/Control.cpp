#include <Arduino.h>
#include "Control.h"
#include "MotorQR/MotorQR.h"


const int timeout = 300;
const uint8_t brightness = 100;

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
    if (!button->isPressedQueueEmpty() && me->timerPressed->isTimeout()){
        while (!button->isPressedQueueEmpty())
        {
            button->popPressedQueue();
        }
        me->timerPressed->restart();
        return 1;
    }
    else
    {
        while (!button->isPressedQueueEmpty())
        {
            button->popPressedQueue();
        }
        return 0;
    }
}

void runControl(void *context){
    tControl *me = (tControl*)context;
    
    if(checkButton(me->buttonUp, me)){
        if(me->currentMotorState == MOTOR_ST_GOINGUP){
            me->motor->stop(me->motor);
        }
        else{
            me->motor->up(me->motor);
        }
    }
    if(checkButton(me->buttonDown, me)){
        if(me->currentMotorState == MOTOR_ST_GOINGDOWN){
            me->motor->stop(me->motor);
        }
        else{
            me->motor->down(me->motor);
        }
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
        //TODO: Think about the SSP maby deinit
        free(me);
        me = NULL;
    }
}


void Control_init(tControl *me, uint8_t buttonGrpNr, tIMotor *motor, tProcess *head, tObserver *observerHead){
    // TODO: Add the context to the Processor
    // TODO: rf
    // me->ssp = new SimpleStateProcessor(CONTROL_ST_UNKNOWN, ControlStateMachine, me);
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
    me->timerPressed = new SimpleSoftTimer(timeout);
    me->timerPressed->start(timeout);
    me->timerPressed->restart();
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
    // TODO: Find out what needs to be in the deinit
}



// SSP_STATE_HANDLER(ControlStateUnknown){
//     tControl *me = (tControl*)context;
//     switch (reason)
//     {
//     case SSP_REASON_ENTER:
//         Serial.println("Control Unknown");
//         me->motor->stop(me->motor);
//         me->buttonUp->LEDoff();
//         me->buttonDown->LEDoff();
//         fsm->NextStateSet(CONTROL_ST_IDLE);
//         break;
//     case SSP_REASON_DO:
//         break;
//     case SSP_REASON_EXIT:
//         break;
//     default:
//         break;
//     }
//     return 0;
// }

// SSP_STATE_HANDLER(ControlStateIdle){
//     tControl *me = (tControl*)context;
//     switch (reason)
//     {
//     case SSP_REASON_ENTER:
//         Serial.println("Control Idle");
//         me->motor->stop(me->motor);
//         break;
//     case SSP_REASON_DO:
//         if (checkButton(me->buttonUp, me))
//         {
//             fsm->NextStateSet(CONTROL_ST_GOINGUP);
//         }
        
//         if (checkButton(me->buttonDown, me))
//         {
//             fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
//         }
        
//         break;
//     case SSP_REASON_EXIT:
//         /* code */
//         break;
//     default:
//         break;
//     }
//     return 0;
// }

// SSP_STATE_HANDLER(ControlStateGoingUp){
//     tControl *me = (tControl*)context;
//     switch (reason)
//     {
//     case SSP_REASON_ENTER:
//         Serial.println("Control GoUp");
//         me->motor->up(me->motor);
//         me->buttonUp->LEDon(100);
//         break;
//     case SSP_REASON_DO:
//         if (checkButton(me->buttonUp, me))
//         {
//             fsm->NextStateSet(CONTROL_ST_IDLE);
//         }

//         if (checkButton(me->buttonDown, me))
//         {
//             fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
//         }
//         break;
//     case SSP_REASON_EXIT:
//         me->buttonUp->LEDoff();
//         break;
//     default:
//         break;
//     }
//     return 0;
// }

// SSP_STATE_HANDLER(ControlStateGoingDown){
//     tControl *me = (tControl*)context;
//     switch (reason)
//     {
//     case SSP_REASON_ENTER:
//         Serial.println("Control GoDown");
//         me->motor->down(me->motor);
//         me->buttonDown->LEDon(100);
//         break;
//     case SSP_REASON_DO:
//         if (checkButton(me->buttonUp, me))
//         {
//             fsm->NextStateSet(CONTROL_ST_GOINGUP);
//         }

//         if (checkButton(me->buttonDown, me))
//         {
//             fsm->NextStateSet(CONTROL_ST_IDLE);
//         }
//         break;
//     case SSP_REASON_EXIT:
//         me->buttonDown->LEDoff();
//         break;
//     default:
//         break;
//     }
//     return 0;
// }