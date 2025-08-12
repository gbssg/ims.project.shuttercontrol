#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "NetworkServer.h"
#include "secrets.h"

int wifiTryCount;

void connectWifi()
{
    wifiTryCount = 0;
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED && wifiTryCount < 20) {
        delay(500);
        Serial.print(".");
        wifiTryCount++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.print("Wifi Connected");
        Serial.println("");
    }
    else
    {
        Serial.println("");
        Serial.print("Connection Failed");
        Serial.println("");
    }
}

void handleClient()
{
    
}