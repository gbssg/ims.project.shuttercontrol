#include <Arduino.h>
#include "Control/Control.h"
#include "MotorQR/MotorQR.h"
#include "Scheduler/Scheduler.h"
#include "NetworkServer/NetworkServer.h"

tControl  *control;
tControl  *control1;
tMotorQR  *motor;
tMotorQR  *motor1;

tProcess  *head;
tObserver *observerHead;

void setup()
{
    // Needed When using Qwiic Components
    Wire.begin();
    Serial.begin(115200);
    head = (tProcess*)calloc(1, sizeof(tProcess));
    observerHead = (tObserver*)calloc(1, sizeof(tObserver));

    motor = MotorQR_create(0, head, observerHead);
    motor1 = MotorQR_create(1, head, observerHead);
    
    control = Control_create(0, &motor->motor, head, observerHead);
    control1 = Control_create(1, &motor1->motor, head, observerHead);

    connectWifi();
    setupAPI();
}

void loop() 
{
    runAll(head);
    handleClient();
}