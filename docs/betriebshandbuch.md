# Operation manual

## Infrastructure

### Environment

The motors should be equipped with a limit switch. Shutters with an integrated control systems are not compatible most of the time. In theory, every shutter that is equipped with control wires can be used. These have to be activated as long as the shutter should go in a direction. In the current configuration it's only possible for motors with wires for up and down (left/right). 

### Hardware

An ESP32 with the Arduino framework was used. The software should work with any other I2C-compatible microcontrollers, as long as they are compatible with the Arduino framework. Currently, the buttons and the relays have to be the Qwiic Buttons and Quad Relay (discontinued as of 12.05.2026) from SparkFun.

## Installation 

Most of the time there are two or three phases and a neutral wire. The respective phases have to be connected to the Quad Relay in this way:

| Motor   | Direction | NO Contact | COM Contact |
| ------- | --------- | ---------- | ----------- |
| Motor 1 | Up        | 1NO        | 1COM        |
| Motor 1 | Down      | 2NO        | 2COM        |
| Motor 2 | Up        | 3NO        | 3COM        |
| Motor 2 | Down      | 4NO        | 4COM        |

![](img/schema-v2.svg)

If the motor is equipped with 3 control wires and 1 phase, there is a choice between letting it go down completely or having it go down with the slits open. Depending on the preference, one of these can be connected with the down direction.

## Configuration

### Config-API (`/config`)

#### Request

`PATCH http://<your ip>/config`

#### Header

|  Name   |  Type  | Required |                         Description                         |
| :-----: | :----: | :------: | :---------------------------------------------------------: |
| api_key | string |   yes    | This has to be the API-key that is defined in the secrets.h |

#### Parameters (JSON)

|    Name    | Type  | Required |                                                                      Description                                                                      |
| :--------: | :---: | :------: | :---------------------------------------------------------------------------------------------------------------------------------------------------: |
| switchTime |  int  |    no    | The time the relays wait for until they switch. The time has to be between 500ms - 5000ms. Without the delay, it could damage the relay or the motor. |
| maxRuntime |  int  |    no    |                            The time the shutters should run. Has to be between 0 and 180000. It updates the `standardTime`                            |

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

When pressing the buttons shortly (< 300ms), the shutter will run for 300ms and stops again.

When pressing the buttons long (> 300ms), the shutter will run completely up or down. The motor stops when the button is pressed again.

When pressing the button for the other side while the motor is still running, the motor will stop and will proceed to go in the other direction after the switchTime has run out.

### Motor API

#### Request

`GET http://<your ip>/motor?id=<id>&cmd=<command>&time=<ms>`

#### Parameters

| Name  |  Type   | Required |                                             Description                                              |
| :---: | :----: | :------: | :--------------------------------------------------------------------------------------------------: |
|  id   |  int   |   yes    |                           The id of the motor that needs to be controlled.                           |
|  cmd  | string |   yes    |                           Command to be executed: `up`, `down`, or `stop`.                           |
| time  |  int   |    no    | Runtime in ms. The motor stops automatically after that time. If not set, the `standardTime` is used. |

#### Example:

```bash
curl "http://<your ip>/motor?id=2&cmd=up&time=1000"
```

### Updating the software

The software can be updated by re-uploading the code with PlatformIO. The newest version of the software is available on the [github repository](https://github.com/gbssg/ims.project.shuttercontrol).

### Troubleshooting

If the output of the serial monitor is unreadable, check if the processor allows the baudrate of 115200 and if the baudrate in the platformio.ini is set to the same baudrate. If the processor doesn't support it, you have to change it in the main.cpp and the platformio.ini.

If any other problems occur, create an [issue](https://github.com/gbssg/ims.project.shuttercontrol/issues).