

#include <Arduino.h>
#include <HardwareSetup.h>
#include <ControlLogic.h>
#include <MotorLogic.h>

// using namespace HolisticSolutions;

void setup() 
{
  Serial.begin(115200);
  setupHardware();
  // setupServer();
  setupControl();
  setupMotor();
}

void loop() 
{
  //do not use testingControl during running runMotor it will cause problems!
  // testingControl();
  // running State Machine
  runMotor();
}