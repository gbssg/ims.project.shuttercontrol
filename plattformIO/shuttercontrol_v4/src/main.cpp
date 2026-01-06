#include <Arduino.h>
#include "Control/Control.h"
#include "MotorQR/MotorQR.h"
#include "Scheduler/Scheduler.h"
#include "NetworkServer/NetworkServer.h"

tControl *control;
tControl *control1;
tMotorQR *motor;
tMotorQR *motor1;

tProcess *head;

void setup()
{
    // Needed When using Qwiic Components
    Wire.begin();
    Serial.begin(115200);
    head = (tProcess*)calloc(1, sizeof(tProcess));

    motor = MotorQR_create(0, head);
    motor1 = MotorQR_create(1, head);
    
    control = Control_create(0, &motor->motor, head);
    control1 = Control_create(1, &motor1->motor, head);

    connectWifi();
    setupAPI();
}

void loop() 
{
    runAll(head);
    handleClient();
}