#include <Arduino.h>
#include <Control.h>


void setup() 
{
    Serial.begin(115200);
    delay(1000);
    control1 -> run();
    control2 -> run();
    
}

void loop() 
{

} 