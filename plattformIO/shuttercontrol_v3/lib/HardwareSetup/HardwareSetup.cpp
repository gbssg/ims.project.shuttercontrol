// The Setup of the Qwiic Devices for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#include <Arduino.h>
#include "HardwareSetup.h"

Qwiic_Relay quadRelay(RELAY_ADDRESS);
QwiicButton buttonUp1;
QwiicButton buttonDown1;
QwiicButton buttonUp2;
QwiicButton buttonDown2;

void setupHardware()
{
    Wire.begin();
    if (!quadRelay.begin())
    {
        Serial.println("Connection to QuadRelay Failed");
    }
    else
    {
        quadRelay.turnAllRelaysOff();
    }
    if (!buttonUp1.begin(BUTTONUP1_ADDRESS))
    {
        Serial.println("Button 1 not connected");
    }
    if (!buttonDown1.begin(BUTTONDOWN1_ADDRESS))
    {
        Serial.println("Button 2 not connected");
    }
    if (!buttonUp2.begin(BUTTONUP2_ADDRESS))
    {
        Serial.println("Button 3 not connected");
    }
    if (!buttonDown2.begin(BUTTONDOWN2_ADDRESS))
    {
        Serial.println("Button 4 not connected");
    }

    buttonUp1.LEDoff();
    buttonDown1.LEDoff();

    // LED config if neded
    // buttonUp1.LEDconfig(0,0,0);
    // buttonDown1.LEDconfig(0,0,0);
    // buttonUp2.LEDconfig(0,0,0);
    // buttonDown2.LEDconfig(0,0,0);
}