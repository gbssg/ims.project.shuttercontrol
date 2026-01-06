#pragma once

#include "IMotor/IMotor.h"

void addMotorServer(uint8_t id, tIMotor *motor);
void connectWifi();
void setupAPI();
void handleClient();