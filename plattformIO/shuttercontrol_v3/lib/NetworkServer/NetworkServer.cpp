// Setup and Handling of the API for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <GlobalVariables.h>
#include "NetworkServer.h"

// you need to make your own secrets.h file to connect to your Nertwork
// plattformIO\shuttercontrol_v3\lib\secrets\secrets.h
// Template:
// #pragma once
// 
// const char *WIFI_SSID = "<SSID>"
// const char *WIFI_PASSWORD = "<PASSWORD>"

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
        Serial.println("Wifi Connected");
        Serial.println(WiFi.localIP());
        Serial.println(WiFi.getHostname());
        Serial.println("");
    }
    else
    {
        Serial.println("");
        Serial.print("Connection Failed");
        Serial.println("");
    }
}

WebServer server(80);

void setupAPI()
{
    // Testing
    server.on("/Up1", []() {
        Serial.println("Up1");
        server.send(200, "text/plain", "Up1");
        _controlmotor = CONTROLMOTOR_UP;

    });

    server.on("/Down1", []() {
        Serial.println("Down1");
        server.send(200, "text/plain", "Down1");
        _controlmotor = CONTROLMOTOR_DOWN;
    });

    server.on("/Stop1", []() {
        Serial.println("Stop1");
        server.send(200, "text/plain", "Stop1");
        _controlmotor = CONTROLMOTOR_STOP;
    });

    // server.on("/Up2", []() {
    //     Serial.println("Up2");
    //     server.send(200, "text/plain", "Up2");
    //  change if you use 2 shutters
    //     _controlmotor = CONTROLMOTOR_UP;

    // });

    // server.on("/Down2", []() {
    //     Serial.println("Down2");
    //     server.send(200, "text/plain", "Down2");
    //  change if you use 2 shutters
    //     _controlmotor = CONTROLMOTOR_DOWN;
    // });

    // server.on("/Stop2", []() {
    //     Serial.println("Stop2");
    //     server.send(200, "text/plain", "Stop2");
    //  change if you use 2 shutters
    //     _controlmotor = CONTROLMOTOR_STOP;
    // });

    server.begin();
}

void handleClient()
{
    server.handleClient();
}