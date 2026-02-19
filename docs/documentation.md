# Dokumentation

## Inhaltsverzeichnis

1. [Einleitung](#einleitung)  
   1.1 [Ziel des Projekts](#ziel-des-projekts)  
   1.2 [Verwendete Hardware (ESP32 & Qwiic)](#verwendete-hardware-esp32--qwiic)  
   1.3 [Architekturüberblick](#architekturüberblick)  
   1.4 [Limitierungen](#limitierungen)  
        1.4.1 [Quad Relais](#quad-relais)  

2. [Systemarchitektur](#systemarchitektur)  
   2.1 [Objektorientiertes C-Konzept](#objektorientiertes-c-konzept)  
   2.2 [I2C-Kommunikation](#i2c-kommunikation)  
   2.3 [Steckverbindungs-Konzept](#steckverbindungs-konzept)  

3. [Programmstruktur](#programmstruktur)  
   3.1 [Main](#main)  
        3.1.1 [Setup](#setup)  
        3.1.2 [Loop](#loop)  

   3.2 [Scheduler](#scheduler)  
        3.2.1 [runAll](#runall)  
        3.2.2 [addRunnable](#addrunnable)  
        3.2.3 [addRunnableStart](#addrunnablestart)  

   3.3 [IRun Interface](#irun-interface)  

   3.4 [IMotor Interface](#imotor-interface)  
        3.4.1 [sIMotor Struktur](#simotor-struktur)  

   3.5 [MotorQR](#motorqr)  
        3.5.1 [Zustandsdiagramm](#zustandsdiagramm-motor)  

   3.6 [Control](#control)  
        3.6.1 [Zustandsdiagramm](#zustandsdiagramm-control)  

4. [Verwendete Libraries](#verwendete-libraries)  
   4.1 [SparkFun Qwiic Button Arduino Library](#sparkfun-qwiic-button-arduino-library)  
        4.1.1 [Verwendete Funktionen](#verwendete-funktionen-button)  

   4.2 [SparkFun Qwiic Relay Arduino Library](#sparkfun-qwiic-relay-arduino-library)  

   4.3 [SimpleStateProcessor](#simplestateprocessor)  
        4.3.1 [Repository](#repository-simplestateprocessor)  

   4.4 [SimpleSoftTimer](#simplesofttimer)  
        4.4.1 [Repository](#repository-simplesofttimer)  

   4.5 [NetworkServer](#networkserver)  
        4.5.1 [WLAN](#wlan)  
        4.5.2 [API](#api)  

5. [API Dokumentation](#api-dokumentation)  
   5.1 [Befehle](#befehle)  
   5.2 [Parameter](#parameter)  
   5.3 [Response Codes](#response-codes)  

6. [Hardware-Schemas](#hardware-schemas)  
   6.1 [Schema der Drehschalter](#schema-der-drehschalter)  
   6.2 [Schema aller Komponenten](#schema-aller-komponenten)  
   6.3 [Schema der Relays](#schema-der-relays)  

## Übersicht

Das Ziel des Projekts ist die Steuerung der Jalousien zu vereinfachen durch eine Steuerung per Website/App.
Dafür wurde ein ESP32 mit Qwiic-Hardware verwendet.

Dieses Projekt nutzt objektorientiertes C, um eine leichte Erweiterbarkeit zu gewährleisten.
Der Code nutzt I2C um mit den verschiedenen Hardware-Komponenten zu kommunizieren.
Das Projekt wird mit Steckverbindungen eingebaut für einen schnellen Wechsel zwischen den Drehschaltern und diesem Projekt.

### Limitirungen

#### Quad Relais

Es gewährleistet in der Theorie bis zu 112 (128 - Reservierte) Quad Relais ohne Buttons, das heisst je nach konfiguration 224 Rolläden. 
Das ist aber nur Thoretisch und kann die Preformance stark, das Speicherlimit des ESP32 könnte auch überschritten werden und die Signalstärke kann nachlassen.
Je nach Konfiguration können es auch weniger sein.

## Libraries / Klassen

### UML

![UML shuttercontrol](img/UML-shuttercontroll_v3.png)

### Main

Ruft alle Initialisierungen auf und führt dann im Loop den Scheduler und die API aus.

Setup:

- Motoren erstellen
- Control erstellen
- WLAN verbinden
- API initialisieren/starten

Loop:

- Scheduler ausführen
- API-Clients verarbeiten


### Scheduler

Ruft alle Run-Funktionen auf, diese werden mit dem IRun Interface implementiert.
Es wird nur eine Liste dieser Funktionen erstellt und anschliessend ausgeführt, es hat keine spezielle Logik dahinter.

runAll:

- führt alle Funktionen der Runnable-Liste aus

addRunable:

- fügt ausführbare funktion (IRun) am Ende der Liste ein.

addRunnableStart

- fügt ausführbare funktion (IRun) am Anfang der Liste ein.

### IRun

Ein Interface für die Scheduler-Funktionen für bessere Skalierbarkeit.

### IMotor

Das Interface, das verschiedene Motoren erlaubt um die Skalierbarkeit zu vereinfachen.

sIMotor: 

- direction Function Pointer
- getState Function Pointer
- getStateName Function Pointer
- command enum
- Void Pointer context

### MotorQR

Implementiert das IMotor Interface um die Relays mit der Motor Logik zu steuern.

#### Zustandsdiagramm
![Zustandsdiagramm des Motors](img/Zustandsdiagramm-Motor_v5.png)

### Control

Liest die Buttons mit der Qwiic Button Library ab. Das Zustandsdiagramm 

#### Zustandsdiagramm

![Zustandsdiagramm des Control Mechanismus](img/Zustandsdiagramm-Control_v4.png)

### SparkFun_Qwiic_Button_Arduino_Library

Standard Library für das auslesen der Buttons.

In diesem Projekt werden die folgenden Funktionen verwendet:
- isPressedQueueEmpty
- popPressedQueue
- LEDon
- LEDoff

### SparkFun_Qwiic_Relay_Arduino_Library

Standard Library für das Steuern der Relays.

### SimpleStateProcessor

Eine Klasse die von holisticsolutions (Niederer Engineering GmbH) bereitgestellt wird, um die Erstellung von Zustandsdiagrammen in C++ zu vereinfachen. 

Repository:

<https://github.com/holisticsolutions/SimpleStateProcessor>

### SimpleSoftTimer

Eine Klasse die von holisticsolutions (Niederer Engineering GmbH) bereitgestellt wird, um die Erstellung von Timern in C++ zu vereinfachen. 
Die Timer sind so ausgelegt das man zwischen start und ende code laufen kann, im gegensatz zu sleep der alles blockiert.

<https://github.com/holisticsolutions/Arduino.SimpleSoftTimer>

### NetworkServer

Stellt die Funktionen zum Verbinden mit WLAN, dem Handling und dem Erstellen der API. Diese Funktionen werden im Main ausgeführt.

#### WLAN

Das WLAN wird mit der WiFi.h library aufgesetzt. Es braucht ein secrets.h file um die Verbindung herzustellen. 

#### API

Die API kann die Befehle up, down und stop entgegennehmen, mit der id der Jalousie die man ansteuern will.

Parameter:
- id (int): ID der Jalousie (startet mit 1)
- cmd (string): up, down, stop, getHeight

Response:
- 400 Invalid command
- 404 Motor not found
- 200 OK
- 200 {height: }



## Schemas

### Schema der Drehschalter 

![Diagramm der Schalter](img/Wiring_Diagramm-Old.png)

### Schema aller Komponenten

![Diagramm der neuen Komponenten](img/Wiring_Diagram_allComponents.png)

### Schema der Relays
![Diagramm der Relays](img/Wiring_Diagram-relayOnly.png)