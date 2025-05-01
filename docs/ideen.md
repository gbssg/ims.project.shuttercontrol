# Ideen

## Übersicht

|                         |                                                         |                                               |                                             |                   |
|:-----------------------:|:-------------------------------------------------------:|:---------------------------------------------:|:-------------------------------------------:|:-----------------:|
| **Physische Schaltung** | [Schalter mit Rückstellung](#schalter-mit-rückstellung) | [Schalter Modifiziert](#schalter-modifiziert) | [Touchscreen](#touchscreen)                 | **[Taster](#taster)** |
| **Virtuelle Schaltung** | **[App](#app)**                                             | **[Website](#website)**                           | [API Jiffy](#api-jiffy) evtl. später                    |                   |
| **Verbindung**          | [Bluetooth](#bluetooth)                                 | **[W-Lan](#w-lan)**                               |                                             |                   |
| **Standanzeige**        | [Ja, App/Website](#ja-appwebsite)                       | [Ja, Bildschirm](#ja-bildschirm)              | **[Nein](#nein)**                               |                   |
| **Resetsystem**         | **[Ja, Admin](#ja-admin)**                                  | [Ja, App/Website](#ja-appwebseite)            | [Bei Neustart](#bei-neustart)               |                   |
| **Zugriffsbegrenzung**  | **[W-Lan](#w-lan1)**                                        | [Bluethooth Beacon](#bluetooth-beacon)        | [Anfragen pro Minute](#anfragen-pro-minute) | [Keine](#keine)   |


## Physische Schaltung

### Schalter mit Rückstellung

#### Beschreibung

Ein Schalter der sich automatisch an den Ausgangspunkt zurück stellt. 

#### Vorteile

Keine Probleme mit Stellungen bei welchen die Schalter von Hand auf null und wieder auf Hoch/Runter gestellt werden muss.

#### Nachteile

Zusätzliche steuerung des Schalters.

### Taster

#### Beschreibung

Taster die beim Drücken Hoch und Runter steuern. 

#### Vorteile

Keine Rückstellung nötig.

#### Nachteile

Zusätzliche Geräte notwendig.

### Schalter modifiziert

#### Beschreibung

Die jetzigen Schalter so modifizieren das diese nicht mehr einrasten.

#### Vorteile

Jetzige Schalter bleiben bestehen

#### Nachteile

Federn sind Abgenutzt Schalter drehen nicht leicht zurück.

### Touchscreen

#### Beschreibung

Touchsreen mit GUI das ähnlich aufgebaut ist wie die Website/App. 

#### Vorteile

Man kann variable Interfaces machen

#### Nachteile

Es werden zusätzliche Resourcen genutzt um das Bild anzuzeigen.

## Virtuelle Schaltung

### App

#### Beschreibung

Installierbare App die automatisch eine Verbindung aufbaut und ein Interface für diverse Einstellungen. Rauf Runter für beide Seiten.

#### Vorteile

Leichte bedienung 

#### Nachteile

Braucht Speicher

### Website

#### Beschreibung

Webseite die geöffnet werden kann und ein GUI aufweist.

#### Vorteile

Die verbindung per W-Lan wäre vereingfacht.

#### Nachteile

Kann nicht ohne Internet genutzt werden.

### API Jiffy

#### Beschreibung

Eine API die im Projekt Jiffy(Zeiterfassung) implementirt werden kann

#### Vorteile

Gleiche Anwendung für Zeiterfassung und Jalousien

#### Nachteile

Login nötig für Jalousien. Keinen Zusammenhang

## Verbindung

### W-Lan

#### Beschreibung

Der ESP32 wird mit dem W-Lan verbunden und kann dan per IP angesprochen werden.

#### Vorteile

Es können relativ leicht pakete gesendet werden

#### Nachteile

Die Netzwerkverbindung kann abbrechen

### Bluetooth

#### Beschreibung

Der ESP32 wird per Bluetooth verbunden

#### Vorteile

Die pakete können schnell gesendet werden.

#### Nachteile

Kleine Distanz, begrenzt geräte.

## Standanzeige

### Ja, App/Website

#### Beschreibung

Auf der App wird der aktuelle stand der Jalousie angezeigt.

#### Vorteile

Man kann den aktuellen Stand von überall sehen.

#### Nachteile

Man muss die Position bestimmen was nur per 

### Ja, Bildschirm

#### Beschreibung

Es wird ein zusätzlicher Bildschirm angeschlossen der den Stand anzeigt.

#### Vorteile

Man kann den Stand überprüfen

#### Nachteile

Es braucht einen Zusätzlichen Bildschirm und evtl. microcontroller.

### Nein

#### Beschreibung

Es wird keine Standanzeige gegeben. 

#### Vorteile

Keine zusätzlichen Tasks für den ESP32

#### Nachteile

Falls Voreinstellungen genutzt werden muss der stand neu aufgenommen werden.

## Resetsystem

### Ja, Admin

#### Beschreibung

Das System kann von einem Administrator Rekalibriet und zurückgesetzt werden.

#### Vorteile

Nötige Systemrestarts können gemacht werden.

#### Nachteile

Falls der Administrator fehlt gibt es keine Restart möglichkeit.

### Ja, App/Webseite

#### Beschreibung

Man kann das System per Webseite Reseten und Rekalibrieren.

#### Vorteile

Der Reset kann immer ausgeführt werden

#### Nachteile

Kann ausgenutzt werden.

### Bei Neustart

#### Beschreibung

Das System wird bei einem Neustart rekalibriert und zurückgesetzt.

#### Vorteile

Immer Kalibriert wenn man das System Neu startet.

#### Nachteile

Es braucht länger um Aufzustarten.

### Automatisch

#### Beschreibung

Das System wird automatisch nach einer gewissen Zeit Rekalibriert und Zurückgesetzt.

#### Vorteile

Immer Aktuell kalibriert

#### Nachteile

Kalibrierung kann falsch liegen

### Nein

#### Beschreibung

Das System braucht keinen Reset da es keine Standortvberfolgung der Jalousiene hat.

#### Vorteile

Keine Zusätzliche Codefragemnte.

#### Nachteile

Keine Neustartfunktion, performance einbusse

## Zugriffsbegrenzung

### W-Lan

#### Beschreibung

Man kann nur im Gleichen Netztwerk auf die Jalousien zugreifen.

#### Vorteile

Keine Externe Verbindung nötig.

#### Nachteile

(Es kann nicht von überall bedient werden.)

### Bluetooth Beacon

#### Beschreibung

Ein Bluetooth Beacon der aussagt ob die Person nahe genug ist um die Jalousien zu steuern.

#### Vorteile

Genaue begrenzung der Distanz

#### Nachteile

Kann nicht ohne Bluetooth genutzt werden.

### Anfragen pro Minute

#### Beschreibung

Eine beschränkung der Anfragen pro Minute zu gewissen Hosts, Schutzt gegen zu oftes Benutzen

#### Vorteile

Kein zu oftes Nutzten

#### Nachteile

Sollte Ausschaltbar sein um zu Testen.

### Keine

#### Beschreibung

Man kann von Überall her Zugreifen.

#### Vorteile

Keine Zusätzlichen Masnahmen nötig

#### Nachteile

Aussenstehende können die Jalousien steuern ohne Vor ort zu sein.
