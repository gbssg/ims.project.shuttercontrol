#include <Arduino.h>
#include <WiFi.h>
#include "NetworkServer.h"
#include "secrets.h"

void connectWifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}
void handleClient()
{
    
}