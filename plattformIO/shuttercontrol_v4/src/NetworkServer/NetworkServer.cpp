// Setup and Handling of the API for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "NetworkServer.h"

#include "MotorQR/MotorQR.h"

// you need to make your own secrets.h file to connect to your Nertwork
// plattformIO\shuttercontrol_v3\lib\secrets\secrets.h
// Template:
// #pragma once
//
// const char *WIFI_SSID = "<SSID>"
// const char *WIFI_PASSWORD = "<PASSWORD>"

#include "secrets/secrets.h"

int wifiTryCount;

typedef struct tMotorNode
{
    struct tMotorNode *next;
    uint8_t id;
    tIMotor *motor;
} tMotorNode;

static tMotorNode motorListHead = {.next = NULL};

void addMotorServer(uint8_t id, tIMotor *motor)
{
    if (!motor)
        return;

    tMotorNode *node = (tMotorNode *)calloc(1, sizeof(tMotorNode));
    if (!node)
        return;

    node->id = id;
    node->motor = motor;

    node->next = motorListHead.next;
    motorListHead.next = node;
}

tIMotor *findMotor(uint8_t id)
{
    for (tMotorNode *n = motorListHead.next; n; n = n->next)
    {
        if (n->id == id)
        {
            return n->motor;
        }
    }
    return NULL;
}

void connectWifi()
{
    wifiTryCount = 0;
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED && wifiTryCount < 20)
    {
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
    server.on("/motor", HTTP_ANY, []() {
    if(!server.hasArg("id") || !server.hasArg("cmd")){
        server.send(400, "text/plain", "Missing arguments");
        return;
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    uint8_t id = server.arg("id").toInt();
    String cmd = server.arg("cmd");

    tIMotor *motor = findMotor(id);
    if (!motor) {
        server.send(404, "text/plain", "Motor not found");
        return;
    }
    if (cmd == "up") {
        motor->up(motor);
    }
    else if (cmd == "down") {
        motor->down(motor);
    }
    else if (cmd == "stop") {
        motor->stop(motor);
    }
    else if (cmd == "getHeight"){
        tMotorQR *motorQR = (tMotorQR*)motor->context;
        int height = motor->getHightPrcentage(motorQR);
        String json = "{\"height\": " + String(height) + "}";
        server.send(200, "application/json", json);
        return;
    }
    else if (cmd == "reset")
    {
        motor->up(motor);
    }
    else {
        server.send(400, "text/plain", "Invalid command");
        return;
    }

    server.send(200, "text/plain", "OK"); });

    server.begin();
}

void handleClient()
{
    server.handleClient();
}