#include <Arduino.h>
#include <Control.h>


void setup() 
{
    Serial.begin(115200);
    Wire.begin();
    Serial.println("Start");
    delay(1000);
    control1->setup(1);
    control2->setup(2);
    
    
}

void loop() 
{
    control1 -> run();
    control2 -> run();
} 