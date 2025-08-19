// Simple State Processor controlling the Relais for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#include <SimpleStateProcessor.h>
#include <SimpleSoftTimer.h>
#include <HardwareSetup.h>
#include <GlobalVariables.h>
#include <ControlLogic.h>
#include <NetworkServer.h>
using namespace HolisticSolutions;


SSP_STATE_HANDLER(MotorStateUnknown);
SSP_STATE_HANDLER(MotorStateIdle);
SSP_STATE_HANDLER(MotorStateIdleUp);
SSP_STATE_HANDLER(MotorStateIdleDown);
SSP_STATE_HANDLER(MotorStateGoingUp);
SSP_STATE_HANDLER(MotorStateGoingDown);
SSP_STATE_HANDLER(MotorStateWaitUp);
SSP_STATE_HANDLER(MotorStateWaitDown);

static const tSSP_State MotorStateMachine[] = {
    SSP_STATE_DESCRIBE("Unknown", MotorStateUnknown),
    SSP_STATE_DESCRIBE("Idle", MotorStateIdle),
    SSP_STATE_DESCRIBE("IdleUp", MotorStateIdleUp),
    SSP_STATE_DESCRIBE("IdleDown", MotorStateIdleDown),
    SSP_STATE_DESCRIBE("goingUp", MotorStateGoingUp),
    SSP_STATE_DESCRIBE("goingDown", MotorStateGoingDown),
    SSP_STATE_DESCRIBE("WaitingUp", MotorStateWaitUp),
    SSP_STATE_DESCRIBE("WaitingDown", MotorStateWaitDown),

    SSP_STATE_LAST()};

static SimpleStateProcessor Motor(MOTOR_ST_UNKNOWN, MotorStateMachine, 0);

SSP_STATE_HANDLER(MotorStateUnknown)
{
  if (reason == SSP_REASON_ENTER)
  {
    fsm->NextStateSet(MOTOR_ST_IDLE);
  }
  if (reason == SSP_REASON_DO)
  {
    runControl();
    handleClient();
  }
  return 0;
}

SSP_STATE_HANDLER(MotorStateIdle)
{
  if (reason == SSP_REASON_ENTER)
  {
    quadRelay.turnRelayOff(1);
    quadRelay.turnRelayOff(2);
    Serial.println("Idle Mot");
  }
  if (reason == SSP_REASON_DO)
  {
    switch (_controlmotor)
    {
    case CONTROLMOTOR_UP:
      fsm->NextStateSet(MOTOR_ST_GOINGUP);
      break;
    case CONTROLMOTOR_DOWN:
      fsm->NextStateSet(MOTOR_ST_GOINGDOWN);
      break;
    default:
      break;
    }
    runControl();
    handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _controlmotor = 0;
  }
  return 0;
}

SSP_STATE_HANDLER(MotorStateIdleUp)
{
  if (reason == SSP_REASON_ENTER)
  {
    quadRelay.turnRelayOff(1);
    quadRelay.turnRelayOff(2);
    _timerUp.restart();
    Serial.println("Idle Up");
  }
  if (reason == SSP_REASON_DO)
  {
    switch (_controlmotor)
    {
    case CONTROLMOTOR_UP:
      fsm->NextStateSet(MOTOR_ST_GOINGUP);
      break;
    case CONTROLMOTOR_DOWN:
      fsm->NextStateSet(MOTOR_ST_WAITUP);
      break;
    default:
      break;
    }
    if (_timerUp.isTimeout())
    {
      fsm->NextStateSet(MOTOR_ST_IDLE);
    }
    runControl();
    handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _controlmotor = 0;
  }
  return 0;
}

SSP_STATE_HANDLER(MotorStateIdleDown)
{
  if (reason == SSP_REASON_ENTER)
  {
    quadRelay.turnRelayOff(1);
    quadRelay.turnRelayOff(2);
    _timerDown.restart();
    Serial.println("Idle Down");
  }
  if (reason == SSP_REASON_DO)
  {
    switch (_controlmotor)
    {
    case CONTROLMOTOR_UP:
      fsm->NextStateSet(MOTOR_ST_WAITDOWN);
      break;
    case CONTROLMOTOR_DOWN:
      fsm->NextStateSet(MOTOR_ST_GOINGDOWN);
      break;
    default:
      break;
    }
    if (_timerDown.isTimeout())
    {
      fsm->NextStateSet(MOTOR_ST_IDLE);
    }
    runControl();
    handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _controlmotor = 0;
  }
  return 0;
}

SSP_STATE_HANDLER(MotorStateGoingUp)
{
  if (reason == SSP_REASON_ENTER)
  {
    quadRelay.turnRelayOn(1);
    Serial.println("Going Up");
    buttonUp1.LEDon();
    _timerStop.restart();
  }
  if (reason == SSP_REASON_DO)
  {
    switch (_controlmotor)
    {
    case CONTROLMOTOR_DOWN:
      fsm->NextStateSet(MOTOR_ST_WAITUP);
      break;
    case CONTROLMOTOR_STOP:
      fsm->NextStateSet(MOTOR_ST_IDLEUP);
      break;
    default:
      break;
    }
    if (_timerStop.isTimeout() && useTimer)
    {
      fsm->NextStateSet(MOTOR_ST_IDLEUP);
    }
    runControl();
    handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _timerUp.restart();
    _controlmotor = 0;
    quadRelay.turnRelayOff(1);
    buttonUp1.LEDoff();
  }

  return 0;
}

SSP_STATE_HANDLER(MotorStateGoingDown)
{
  if (reason == SSP_REASON_ENTER)
  {
    quadRelay.turnRelayOn(2);
    Serial.println("Going Down");
    buttonDown1.LEDon();
    _timerStop.restart();
  }
  if (reason == SSP_REASON_DO)
  {
    switch (_controlmotor)
    {
    case CONTROLMOTOR_UP:
      fsm->NextStateSet(MOTOR_ST_WAITDOWN);
      break;
    case CONTROLMOTOR_STOP:
      fsm->NextStateSet(MOTOR_ST_IDLEDOWN);
      break;
    default:
      break;
    }
    if (_timerStop.isTimeout() && useTimer)
    {
      fsm->NextStateSet(MOTOR_ST_IDLEDOWN);
    }
    runControl();
    handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _timerDown.restart();
    _controlmotor = 0;
    quadRelay.turnRelayOff(2);
    buttonDown1.LEDoff();
  }
  return 0;
}

SSP_STATE_HANDLER(MotorStateWaitUp)
{
  if (reason == SSP_REASON_ENTER)
  {
    Serial.println("Wait Up");
  }
  if (reason == SSP_REASON_DO)
  {
    if (_timerUp.isTimeout())
    {
      fsm->NextStateSet(MOTOR_ST_GOINGDOWN);
    }
  }
  if (reason == SSP_REASON_EXIT)
  {
    _controlmotor = 0;
  }
  return 0;
}

SSP_STATE_HANDLER(MotorStateWaitDown)
{
  if (reason == SSP_REASON_ENTER)
  {
    Serial.println("Wait Down");
  }
  if (reason == SSP_REASON_DO)
  {
    if (_timerDown.isTimeout())
    {
      fsm->NextStateSet(MOTOR_ST_GOINGUP);
    }
  }
  if (reason == SSP_REASON_EXIT)
  {
    _controlmotor = 0;
  }
  return 0;
}

void setupMotor()
{
    Motor.reset();
}

void runMotor()
{
    Motor.run();
}

uintptr_t getMotorState()
{
    return Motor.CurrentStateGet();
}