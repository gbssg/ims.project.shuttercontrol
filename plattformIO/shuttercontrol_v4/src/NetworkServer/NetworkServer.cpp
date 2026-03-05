// Setup and Handling of the API for the project "shuttercontroll"
// Autor: Bastian Lehmann, IMS-T

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "NetworkServer.h"
#include <ArduinoJson.h>

#include <EEPROM.h>

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
int standardTime;


void setupAPI()
{
    EEPROM.get(0, standardTime);
    // Testing
    server.on("/motor", HTTP_ANY, []() {
    if(!server.hasArg("id") || !server.hasArg("cmd")){
        server.send(400, "application/json", "Missing arguments");
        return;
    }
    uint8_t id = server.arg("id").toInt();
    String cmd = server.arg("cmd");

    tIMotor *motor = findMotor(id);
    if (!motor) {
        server.send(404, "application/json", "Motor not found");
        return;
    }

    if (server.hasArg("time")) {
        motor->time = server.arg("time").toInt();
    }
    else {
        motor->time = standardTime;
    }

    if (cmd == "up") {
        motor->startTime = millis();
        motor->up(motor);
    }
    else if (cmd == "down") {
        motor->startTime = millis();
        motor->down(motor);
    }
    else if (cmd == "stop") {
        motor->startTime = millis();
        motor->stop(motor);
    }
    else {
        server.send(400, "application/json", "Invalid command");
        return;
    }

    server.send(200, "application/json", "OK"); });

    server.on("/config", HTTP_PATCH, []{
        Serial.println(server.header("api_key"));
        if (server.header("api_key") != API_KEY) {
            server.send(401, "application/json", "Unauthorized");
            return;
        }

        if (!server.hasArg("plain"))
        {
            server.send(400, "application/json", "Missing body");
            return;
        }
        
        String body = server.arg("plain");
        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            server.send(400, "application/json", "Invalid JSON");
            return;
        }

        if (doc.containsKey("switchTime"))
        {
            int switchTime = doc["switchTime"];
            if (switchTime >= 500 && switchTime <= 5000) {
                EEPROM.put(127, switchTime);
                EEPROM.commit();
            }
            else {
                server.send(400, "application/json", "SwitchTime out of Bounds");
            }
        }

        if (doc.containsKey("maxRuntime"))
        {
            int maxRuntime = doc["maxRuntime"];
            if (maxRuntime >= 0 && maxRuntime <= 180000) {
                EEPROM.put(0, maxRuntime);
                EEPROM.commit();
                standardTime = maxRuntime;
            }
            else {
                server.send(400, "application/json", "maxRunTime out of Bounds");
            }
        }


        server.send(200, "application/json", "Times have been Changed");
    });

    const char* headerKeys[] = {"api_key"};
    size_t headerKeysCount = 1;

    server.collectHeaders(headerKeys, headerKeysCount);

    server.begin();
}

void checkTimeout(tIMotor *motor) {
    if ((millis() - motor->startTime) > motor->time && motor->time != 0) {
        motor->time = 0;
        motor->stop(motor);
    }
}

void checkAllMotors() {
    for (tMotorNode *n = motorListHead.next; n; n = n->next)
    {
        if (n->id)
        {
            checkTimeout(n->motor);
        }
    }
}

void handleClient()
{
    server.handleClient();
    checkAllMotors();
}