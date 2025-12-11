#include <Arduino.h>
#include "Control/Control.h"
#include "MotorQR/MotorQR.h"
#include "Scheduler/Scheduler.h"

tControl *control;
tControl *control1;
tMotorQR *motor;
tMotorQR *motor1;

void setup()
{
    // Needed When using Qwiic Components
    Wire.begin();
    Serial.begin(115200);
    motor = MotorQR_create(0);
    motor1 = MotorQR_create(1);
    
    control = Control_create(0, &motor->motor);
    control1 = Control_create(1, &motor1->motor);
    Serial.println(control->button->addrUp);
    Serial.print("Debounce Time: ");
    Serial.println(control->buttonUp->getDebounceTime());
}

void loop() 
{
    // control->run(control);
    control->ssp->run();
    control1->ssp->run();
    motor1->ssp->run();
    motor->ssp->run();
}