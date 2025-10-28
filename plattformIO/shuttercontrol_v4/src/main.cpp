#include <Arduino.h>
#include <Control.h>
#include <Motor.h>

tMotor motor1;
tControl control1;
QwiicButton buttonUp1;
QwiicButton buttonDown1;

void setup() 
{
    Serial.begin(115200);
    Motor(&motor1, 0);
    setupControl(&control1, &motor1, 0, buttonUp1, buttonDown1);
}

void loop() 
{

}