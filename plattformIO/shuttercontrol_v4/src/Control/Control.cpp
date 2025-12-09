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

tControl *Control_create(uint8_t buttonGrpNr){
    tControl *result = NULL;

    result = (tControl *)calloc(1, sizeof(tControl));
    if (result == NULL)
    {
        goto err_no_memory;
    }

    Control_init(result, buttonGrpNr);

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

void Control_init(tControl *me, uint8_t buttonGrpNr){
    // TODO: Add the context to the Processor
    me->ssp = new SimpleStateProcessor(CONTROL_ST_UNKNOWN, ControlStateMachine, 0);
    me->button = &buttons[buttonGrpNr];
    me->run = Run;
    me->setup = Setup;
}
void Control_deinit(tControl *me){
    // TODO: Find out what needs to be in the deinit
}

SSP_STATE_HANDLER(ControlStateUnknown){
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

SSP_STATE_HANDLER(ControlStateIdle){
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

SSP_STATE_HANDLER(ControlStateGoingUp){
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

SSP_STATE_HANDLER(ControlStateGoingDown){
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