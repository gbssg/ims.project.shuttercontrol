#include <Arduino.h>
#include <Control.h>
#include <Motor.h>
#include <SimpleStateProcessor.h>

tMotor motor1;
tControl control1;
QwiicButton buttonUp1;
QwiicButton buttonDown1;
tButton buttonGrp1;

static SimpleStateProcessor Control1(CONTROL_ST_UNKNOWN, ControlStateMachine, &control1);

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    buttonGrp1.up = &buttonUp1;
    buttonGrp1.down = &buttonDown1; 
    motor1.strategy = &MotorQR; // setting up the strategy
    motor1.strategy->setup(&motor1, 0); // setting up the relay numbers
    control1.ssp = &Control1;
    // setupMotor(&motor1, 0);
    setupControl(&control1, &motor1, 0, &buttonGrp1);
    Serial.println("Setup Complete!");
    control1.ssp->reset();
}

void loop() 
{
    control1.ssp->run();
}

