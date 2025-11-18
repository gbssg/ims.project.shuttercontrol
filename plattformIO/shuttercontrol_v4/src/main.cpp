#include <Arduino.h>
#include "Control/Control.h"
#include "MotorQR/MotorQR.h"
#include "Scheduler/Scheduler.h"

tControl *control;
tMotorQR *motor;

void setup()
{
    Serial.begin(115200);
    control = Control_create(0);
    motor = MotorQR_create(0);
    // Wire.begin();
    control->run(control);
    Serial.println(control->button->addrUp);
}

void loop() 
{
    control->run(control);
}