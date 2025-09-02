# ShutterControl
This Project is used to control Shutters using Qwiic components and an API.

## 

## About
This project was made to control the shutters in my office so none has to walk to the switches. This project makes the shutters controllable through 2 buttons up/down.

## Installation 
The code is made for the PlatformIO extension for visual studio code.
If you want to use this code you have to make an secrets.h file or add your ssid and password (not recomended) to connct to wifi.

### secrets.h
plattformIO\shuttercontrol_v3\lib\secrets\secrets.h
Template:
#pragma once

const char *WIFI_SSID = "<SSID>"
const char *WIFI_PASSWORD = "<PASSWORD>"
