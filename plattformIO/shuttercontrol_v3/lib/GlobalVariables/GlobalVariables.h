// All the global variables for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#pragma once
#include <Arduino.h>
#include <SimpleSoftTimer.h>
using namespace HolisticSolutions;

// Enums for motor control
typedef enum eControlMotor
{
  CONTROLMOTOR_UNKNOWN = 0,
  CONTROLMOTOR_UP,
  CONTROLMOTOR_DOWN,
  CONTROLMOTOR_STOP,

  CONTROLMOTOR_COUNT
} tControlMotor;

typedef enum eControlState
{
  CONTROL_ST_UNKNOWN = 0,
  CONTROL_ST_IDLE,
  CONTROL_ST_GOINGUP,
  CONTROL_ST_GOINGDOWN,

  CONTROL_ST_COUNT
} tControlState;

typedef enum eMotorState
{
  MOTOR_ST_UNKNOWN = 0,
  MOTOR_ST_IDLE,
  MOTOR_ST_IDLEUP,
  MOTOR_ST_IDLEDOWN,
  MOTOR_ST_GOINGUP,
  MOTOR_ST_GOINGDOWN,
  MOTOR_ST_WAITUP,
  MOTOR_ST_WAITDOWN,

  MOTOR_ST_COUNT
} tMotorState;

extern uintptr_t _controlmotor;

static SimpleSoftTimer _timerUp(1000);
static SimpleSoftTimer _timerDown(1000);
static SimpleSoftTimer _timerPressed(300);