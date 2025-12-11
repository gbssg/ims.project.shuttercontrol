#include "Control.h"
#include <Arduino.h>

void Run(tControl *me){
    
}

void Setup(tControl *me){

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

tControl *Control_create(uint8_t buttonGrpNr, tIMotor *motor){
    tControl *result = NULL;

    result = (tControl *)calloc(1, sizeof(tControl));
    if (result == NULL)
    {
        goto err_no_memory;
    }

    Control_init(result, buttonGrpNr, motor);

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

void Control_init(tControl *me, uint8_t buttonGrpNr, tIMotor *motor){
    // TODO: Add the context to the Processor
    me->ssp = new SimpleStateProcessor(CONTROL_ST_UNKNOWN, ControlStateMachine, me);
    me->button = &buttons[buttonGrpNr];
    me->run = Run;
    me->setup = Setup;
    me->buttonUp = new QwiicButton();
    me->buttonDown = new QwiicButton();
    me->buttonUp->begin(me->button->addrUp);
    me->buttonDown->begin(me->button->addrDown);
    me->buttonUp->enableClickedInterrupt();
    me->buttonDown->enableClickedInterrupt();
    me->motor = motor;
}
void Control_deinit(tControl *me){
    // TODO: Find out what needs to be in the deinit
}

int checkButton(QwiicButton* button){
    if (!button->isClickedQueueEmpty()){
        button->LEDon(100);
        while (!button->isClickedQueueEmpty())
        {
            button->popClickedQueue();
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

SSP_STATE_HANDLER(ControlStateUnknown){
    tControl *me = (tControl*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Control Unknown");
        // me->buttonUp->LEDoff();
        // me->buttonDown->LEDoff();
        fsm->NextStateSet(CONTROL_ST_IDLE);
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

SSP_STATE_HANDLER(ControlStateIdle){
    tControl *me = (tControl*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Control Idle");
        break;
    case SSP_REASON_DO:
        if (checkButton(me->buttonUp))
        {
            fsm->NextStateSet(CONTROL_ST_GOINGUP);
        }
        
        // if (!me->buttonUp->isClickedQueueEmpty()){
        //     fsm->NextStateSet(CONTROL_ST_GOINGUP);
        //     me->buttonUp->LEDon(100);
        //     while (!me->buttonUp->isClickedQueueEmpty())
        //     {
        //         me->buttonUp->popClickedQueue();
        //     }
        // }

        // if (me->buttonUp->isPressed() && me->timerPressed->isTimeout())
        // {
        //     me->timerPressed->restart();
        //     fsm->NextStateSet(CONTROL_ST_GOINGUP);
        // }
        
        if (checkButton(me->buttonDown))
        {
            fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
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

SSP_STATE_HANDLER(ControlStateGoingUp){
    tControl *me = (tControl*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Control GoUp");
        me->buttonUp->LEDon(100);
        break;
    case SSP_REASON_DO:
        if (checkButton(me->buttonUp))
        {
            fsm->NextStateSet(CONTROL_ST_IDLE);
        }

        if (checkButton(me->buttonDown))
        {
            fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
        }
        break;
    case SSP_REASON_EXIT:
        me->buttonUp->LEDoff();
        break;
    default:
        break;
    }
    return 0;
}

SSP_STATE_HANDLER(ControlStateGoingDown){
    tControl *me = (tControl*)context;
    switch (reason)
    {
    case SSP_REASON_ENTER:
        Serial.println("Control GoDown");
        me->buttonDown->LEDon(100);
        break;
    case SSP_REASON_DO:
        if (checkButton(me->buttonUp))
        {
            fsm->NextStateSet(CONTROL_ST_GOINGUP);
        }

        if (checkButton(me->buttonDown))
        {
            fsm->NextStateSet(CONTROL_ST_IDLE);
        }
        break;
    case SSP_REASON_EXIT:
        me->buttonDown->LEDoff();
        break;
    default:
        break;
    }
    return 0;
}