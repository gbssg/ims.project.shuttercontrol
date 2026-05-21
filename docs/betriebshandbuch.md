# Operation manual

## Infrastructure

### Environment

The Motors should be equipped with an end switch. The fully self contained shutters cant be used most of the time. In theory can every shutter that is equipped with controlling wires, that have to be activated as long as the shutter should go in an direction. In the current configuration its only possible to motors with wires for up and down (left/right). 

### Hardware

An ESP32 with the arduino framework was used. The Software should work with any other I2C compatible microcontrollers, as long as they are compatibly with the arduino framework. Currently the buttons and the relays have to be the Qwiic Buttons and Quad Relay (Discontinued) from SparkFun (As of 12.05.2026)

## Installation 

Most of the time there are two or three phases and an neutral wire. The respective phases have to be connect to the Quad Relay in this way:

| Motor   | Direction | NO Contact | COM Contact |
| ------- | --------- | ---------- | ----------- |
| Motor 1 | Up        | 1NO        | 1COM        |
| Motor 1 | Down      | 2NO        | 2COM        |
| Motor 2 | Up        | 3NO        | 3COM        |
| Motor 2 | Down      | 4NO        | 4COM        |

![](img/schema-v2.svg)

If the motor is equipped with 3 phases, there is a choice between letting it go down completely or having it go down with some slits open, depending on the preference one of these can be connected with the Down direction.

## Configuration

### Config-API (`/config`)

#### Request

`PATCH http://<your ip>/config`

#### Header

|  Name   |  Typ   | Required |                         Description                         |
| :-----: | :----: | :------: | :----------------------------------------------------------: |
| api_key | string |   yes    | This has to be the API-key that is defined in the secrets.h |

#### Parameters (JSON)

|    Name    |  Typ  | Required |                                                                          Description                                                                           |
| :--------: | :---: | :------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| switchTime |  int  |    no    | The time the relays wait for until they switch. The time has to be between 500ms - 5000ms. Without the delay it could create damages to the relay or the motor. |
| maxRuntime |  int  |    no    |                                 The time the shutters should run. Has to be between 0 and 180000. It updates the `standardTime`                                 |

#### Example
Set the switchTime to 1s and limit the maxRuntime to 1min.

```bash
curl -X "PATCH" \
     -H "api_key: <your API-key>" \
     -H "Content-Type: application/json" \
     -H "Accept: application/json" \
     --json '{"switchTime": 1000,"maxRuntime":60000}' \
     http://<your ip>/config
```

## Operation

### Buttons

When pressing the buttons shortly (< 300ms) the shutter will run for 300ms and stops again.

When pressing the buttons long (> 300ms) the shutter will run completely up or down. The Motor stops when the Button is Pressed again.

When pressing the button for the other Side the motor will stop and will precede to go in the other direction after the switchTime has run out.

### Motor API

#### Request

`GET http://<your ip>/motor?id=<id>&cmd=<command>&time=<ms>`

#### Parameters

| Name  |  Typ   | Required |                                            Description                                            |
| :---: | :----: | :------: | :------------------------------------------------------------------------------------------------: |
|  id   |  int   |   yes    |                         The id of the motor that needs tho be controlled.                          |
|  cmd  | string |   yes    |                         Command to be executed: `up`, `down`, oder `stop`.                         |
| time  |  int   |    no    | Runtime in ms. The motor stops automatically after that time. if not set the `standardTime` is used. |

#### Example:

```bash
curl "http://<your ip>/motor?id=2&cmd=up&time=1000"
```

### Updating the Software

The software can be updated by re-uploading the code with PlatformIO. The newest version of the software is available on the [github repository](https://github.com/gbssg/ims.project.shuttercontrol).

### Troubleshooting

If the output of the serial monitor is unreadable, check if the processor allows the baudrate of 115200 and if the baudrate in the platformio.ini is set to the same baudrate. If the processor doesn't support you have to change it in the main.cpp and the platformio.ini.