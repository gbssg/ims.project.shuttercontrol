# ShutterControl

## Projektbeschreibung

Das Projekt ShutterControl ist eine Jalousiensteuerung für standardmässig zwei Motoren. Diese können per API oder Buttons gesteuert werden. Sie ermöglicht die Steuerung der Jalousien vom Platz aus oder überall im gleichen Netzwerk. Zusätzlich ist es möglich die Steuerung über eine API zu konfigurieren.

## Ausgangslage

Die Ausgangslage war ein Rolladen mit zwei Schaltern. Die Steuerung vom Platz aus war nicht möglich. Man musste jedes Mal aufstehen, um die Schalter zu bedienen. Darum wurde oft die Person neben den Schaltern gebeten, dies zu tun.

## Vision

Das Projekt sollte die Möglichkeit bieten, die Jalousien vom Platz aus zu steuern und so Zeit und Aufwand zu sparen. Zusätzlich muss die Person bei den Schaltern nicht mehr für andere Schalten. Diese Aufgabe sollte nun mit einem mit dem Internet verbundenen ESP32 ausgeführt werden. 

## Getting Started

- Installiere die [PlatformIO](vscode:extension/platformio.platformio-ide)-Erweiterung

- Erstelle die Datei secrets.h

Der API-Key wird für die Config-Api verwendet, falls dieser nicht gesetzt wird kann es zu einem Crash oder einem unautorisierten Zugriff kommen.

> plattformIO\shuttercontrol_v4\lib\secrets\secrets.h

Template:
```h
#pragma once

const char *WIFI_SSID = "<SSID>";
const char *WIFI_PASSWORD = "<PASSWORD>";
const char *API_KEY = "<API_KEY>"; 
```

- Ich nutze diese PlatformIO Konfiguration mit dem ESP32 Micromod von Sparkfun. Wenn ein anderes Board verwendet wird muss es daher angepasst werden.

```ini
[env:sparkfun_esp32micromod]
platform = espressif32
board = sparkfun_esp32micromod
framework = arduino
lib_deps = holisticsolutions/SimpleStateProcessor
           holisticsolutions/SimpleSoftTimer
           bblanchon/ArduinoJson @ ^6.21.3
monitor_speed = 115200
build_flags = -Iinclude
```

- Upload Code mit PlatformIO

## Links

[Betriebshandbuch](docs/betriebshandbuch.md)

[Technische Dokumentation](docs/technischeDokumentation)

[Glossar](docs/glossar.md)

## Kontakt

- Github: [ims.project.shuttercontrol](https://github.com/gbssg/ims.project.shuttercontrol)
- E-Mail: [bastian.lehmann@edu.gbssg.ch](mailto:bastian.lehmann@edu.gbssg.ch)




