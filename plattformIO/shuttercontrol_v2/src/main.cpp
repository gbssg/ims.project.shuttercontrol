/*
Dies ist ein Code zu Testzwecken und Demonstration meines Projekts.
Die Grundfunktionen wurden nur grob Umgesetzt.
B.Lehmann
*/



#include <Arduino.h>
// librarys for communication with qwiic components
#include <Wire.h>
#include <SparkFun_Qwiic_Button.h>
#include <SparkFun_Qwiic_Relay.h>

// librarys for network communication
#include <WiFi.h>
#include <WebServer.h>

// library for simple state machine
#include <SimpleStateProcessor.h>

// library for simple timers
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;


// definition for all addresses
#define RELAY_ADDRESS 0x6D
#define BUTTONUP1_ADDRESS 0x6F
#define BUTTONDOWN1_ADDRESS 0x71
#define BUTTONUP2_ADDRESS 0x72
#define BUTTONDOWN2_ADDRESS 0x73

// initialising of qwiic components
Qwiic_Relay quadRelay(RELAY_ADDRESS);
QwiicButton buttonUp1;
QwiicButton buttonDown1;
QwiicButton buttonUp2;
QwiicButton buttonDown2;

// enumerator for communication betwen comtroler and motordriver
typedef enum eControlMotor
{
  CONTROLMOTOR_UNKNOWN = 0,
  CONTROLMOTOR_UP,
  CONTROLMOTOR_DOWN,
  CONTROLMOTOR_STOP,

  CONTROLMOTOR_COUNT
} tControlMotor;

static uintptr_t _controlmotor = CONTROLMOTOR_UNKNOWN;

// control state diagram definition

typedef enum eControlState
{
  CONTROL_ST_UNKNOWN = 0,
  CONTROL_ST_IDLE,
  CONTROL_ST_GOINGUP,
  CONTROL_ST_GOINGDOWN,

  CONTROL_ST_COUNT
} tControlState;

SSP_STATE_HANDLER(ControlStateUnknown);
SSP_STATE_HANDLER(ControlStateIdle);
SSP_STATE_HANDLER(ControlStateGoingUp);
SSP_STATE_HANDLER(ControlStateGoingDown);

static const tSSP_State ControlStateMachine[] = {
    SSP_STATE_DESCRIBE("Unknown", ControlStateUnknown),
    SSP_STATE_DESCRIBE("Idle", ControlStateIdle),
    SSP_STATE_DESCRIBE("goingUp", ControlStateGoingUp),
    SSP_STATE_DESCRIBE("goingDown", ControlStateGoingDown),

    SSP_STATE_LAST()};

// motor state diagram definition

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

//initialising of state diagramms
static SimpleStateProcessor Control(CONTROL_ST_UNKNOWN, ControlStateMachine, 0);
static SimpleStateProcessor Motor(MOTOR_ST_UNKNOWN, MotorStateMachine, 0);
static uintptr_t _lastState = CONTROL_ST_UNKNOWN;

//initialising of timers
static SimpleSoftTimer _timerUp(1000);
static SimpleSoftTimer _timerDown(1000);
static SimpleSoftTimer _timerPressed(300);

// connection data for wifi
const char* ssid = "Galaxy-A51-Bastian";
const char* password = "Testing25";
WebServer server(80);


void setup()
{

  Serial.begin(115200);
  Wire.begin();

  //starting connection to all components
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

  //changing config of buttons
  buttonUp1.LEDconfig(20, 0, 0);
  buttonDown1.LEDconfig(20,0,0);

  //connecting wifi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //definign server actions
  server.on("/up", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    _controlmotor = CONTROLMOTOR_UP;
    Control.NextStateSet(CONTROL_ST_GOINGUP);
    server.send(200, "text/plain", "Going Up");
  });

  server.on("/down", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    _controlmotor = CONTROLMOTOR_DOWN;
    Control.NextStateSet(CONTROL_ST_GOINGDOWN);
    server.send(200, "text/plain", "Going Down");
  });

  server.on("/stop", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    _controlmotor = CONTROLMOTOR_STOP;
    Control.NextStateSet(CONTROL_ST_IDLE);
    server.send(200, "text/plain", "Stop");
  });

  server.begin();

  Control.reset();
  Motor.reset();
  _timerPressed.start(300);
}

void loop()
{
  Motor.run();
}

// control state diagram

SSP_STATE_HANDLER(ControlStateUnknown)
{
  if (reason == SSP_REASON_ENTER)
  {
    fsm->NextStateSet(CONTROL_ST_IDLE);
    Serial.println("Unknown");
    buttonUp1.LEDon();
    buttonDown1.LEDon();
  }
  if (reason == SSP_REASON_DO)
  {
    Serial.print("Error didnt exit <unknown> cleanly");
  }
  return 0;
}

SSP_STATE_HANDLER(ControlStateIdle)
{
  if (reason == SSP_REASON_ENTER)
  {
    _controlmotor = CONTROLMOTOR_STOP;
    Serial.println("Idle");
    buttonUp1.LEDoff();
    buttonDown1.LEDoff();
  }
  if (reason == SSP_REASON_DO)
  {
    if (buttonUp1.isPressed() && _timerPressed.isTimeout())
    {
      _timerPressed.restart();
      fsm->NextStateSet(CONTROL_ST_GOINGUP);
    }
    if (buttonDown1.isPressed() && _timerPressed.isTimeout())
    {
      _timerPressed.restart();
      fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
    }
  }
  return 0;
}

SSP_STATE_HANDLER(ControlStateGoingUp)
{
  if (reason == SSP_REASON_ENTER)
  {
    _controlmotor = CONTROLMOTOR_UP;
    Serial.println("GoUp");
    buttonUp1.LEDon();
    buttonDown1.LEDoff();
  }
  if (reason == SSP_REASON_DO)
  {
    if (buttonUp1.isPressed() && _timerPressed.isTimeout())
    {
      _timerPressed.restart();
      fsm->NextStateSet(CONTROL_ST_IDLE);
    }
    if (buttonDown1.isPressed() && _timerPressed.isTimeout())
    {
      _timerPressed.restart();
      fsm->NextStateSet(CONTROL_ST_GOINGDOWN);
    }
  }
  return 0;
}

SSP_STATE_HANDLER(ControlStateGoingDown)
{
  if (reason == SSP_REASON_ENTER)
  {
    _controlmotor = CONTROLMOTOR_DOWN;
    Serial.println("GoDown");
    buttonUp1.LEDoff();
    buttonDown1.LEDon();
  }
  if (reason == SSP_REASON_DO)
  {
    if (buttonUp1.isPressed() && _timerPressed.isTimeout())
    {
      _timerPressed.restart();
      fsm->NextStateSet(CONTROL_ST_GOINGUP);
    }
    if (buttonDown1.isPressed() && _timerPressed.isTimeout())
    {
      _timerPressed.restart();
      fsm->NextStateSet(CONTROL_ST_IDLE);
    }
  }
  return 0;
}

// motor state diagram

SSP_STATE_HANDLER(MotorStateUnknown)
{
  if (reason == SSP_REASON_ENTER)
  {
    fsm->NextStateSet(MOTOR_ST_IDLE);
  }
  if (reason == SSP_REASON_DO)
  {
    Control.run();
    server.handleClient();
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
    Control.run();
    server.handleClient();
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
    Control.run();
    server.handleClient();
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
    Control.run();
    server.handleClient();
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
    Control.run();
    server.handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _timerUp.restart();
    _controlmotor = 0;
    quadRelay.turnRelayOff(1);
  }

  return 0;
}

SSP_STATE_HANDLER(MotorStateGoingDown)
{
  if (reason == SSP_REASON_ENTER)
  {
    quadRelay.turnRelayOn(2);
    Serial.println("Going Down");
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
    Control.run();
    server.handleClient();
  }
  if (reason == SSP_REASON_EXIT)
  {
    _timerDown.restart();
    _controlmotor = 0;
    quadRelay.turnRelayOff(2);
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

