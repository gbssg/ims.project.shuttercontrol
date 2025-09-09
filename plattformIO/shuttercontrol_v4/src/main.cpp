#include <Arduino.h>
#include <Control.h>


void setup() 
{
    Serial.begin(115200);
    Wire.begin();
    delay(1000);
    control1->setup();
    control2->setup();
    
    
}

void loop() 
{
    control1 -> run();
    control2 -> run();
} 