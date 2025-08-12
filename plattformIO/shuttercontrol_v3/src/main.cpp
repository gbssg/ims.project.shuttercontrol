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
  connectWifi();
  // setupServer();
  setupControl();
  setupMotor();
}

void loop() 
{
  //do not use testingControl with runMotor it will cause problems!
  // LEDs and Relais can get misaligned
  // testingControl();
  // running State Machine
  runMotor();
}