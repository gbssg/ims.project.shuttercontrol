#include <Arduino.h>
#include <HardwareSetup.h>
#include <ControlLogic.h>
#include <MotorLogic.h>
#include <NetworkServer.h>

// using namespace HolisticSolutions;

void setup() 
{
  Serial.begin(115200);
  setupHardware();
  buttonUp1.LEDconfig(100, 1000, 500, 20);
  buttonDown1.LEDconfig(100, 1000, 500, 20);
  connectWifi();
  setupAPI();
  setupControl();
  setupMotor();
  buttonUp1.LEDoff();
  buttonDown1.LEDoff();
}

void loop() 
{
  // do not use testingControl with runMotor it will cause problems!
  // LEDs and Relais can get misaligned
  // testingControl();
  // running State Machine
  runMotor();
}