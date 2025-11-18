#include "MotorQR.h"
#include <Arduino.h>

void Up(tIMotor *me){

}
void Down(tIMotor *me){

}
void Stop(tIMotor *me){

}

tMotorQR *MotorQR_create()
{
    tMotorQR *result = NULL;

    result = (tMotorQR *)calloc(1, sizeof(tMotorQR));
    if (result == NULL) {
        goto err_no_memory;
    }

    MotorQR_init(result);

    return result;

    free(result);
    result = NULL;

err_no_memory:
    return result;
}
void MotorQR_destroy(tMotorQR *me)
{
    if (me != NULL) {
        free(me);
        me = NULL;
    }
}

void MotorQR_init(tMotorQR *me){
    me->motor.up = Up;
    me->motor.down = Down;
    me->motor.stop = Stop;
}
void MotorQR_deinit(tMotorQR *me){
    //TODO: Find out what needs to be in the deinit
}