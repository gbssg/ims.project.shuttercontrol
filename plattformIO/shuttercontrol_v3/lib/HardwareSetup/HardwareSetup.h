#pragma once
#include <SparkFun_Qwiic_Button.h>
#include <SparkFun_Qwiic_Relay.h>

// To reconfigure the Adresses use the Example Code from Sparkfun

#define RELAY_ADDRESS 0x6D
#define BUTTONUP1_ADDRESS 0x6F
#define BUTTONDOWN1_ADDRESS 0x71
#define BUTTONUP2_ADDRESS 0x72
#define BUTTONDOWN2_ADDRESS 0x73

extern Qwiic_Relay quadRelay;
extern QwiicButton buttonUp1;
extern QwiicButton buttonDown1;
extern QwiicButton buttonUp2;
extern QwiicButton buttonDown2;

void setupHardware();