# ShutterControl

## Project description

ShutterControl is a shutter controller that supports two shutter motors in the standard configuration. These motors can be controlled via an API or buttons. It allows users to control the shutters from any desk or anywhere on the same network.

## Starting point

The room was equipped with two shutters. Each shutter was controlled by its own switch. To control the shutters, a person had to walk to the switches or the person next to them was asked to open or close them.

## Vision

The project should allow users to control the shutters from any desk, which saves time. Additionally, the person next to the switches doesn't have to control the shutters for anyone else. This should be achieved with an ESP32 that is connected to the local network, while still providing physical control for people who cannot use the API.

## Getting Started

- Install the Visual Studio Code extension for [PlatformIO](vscode:extension/platformio.platformio-ide)
- Create the file secrets.h in the folder `platformIO/shuttercontrol/src/secrets/` with this template: `platformIO/shuttercontrol/src/secrets/template.secrets.h`
  - If the API key is not set, there is a possibility of crashes or unauthorized access. 
- Upload the code with PlatformIO



## Further reading

- [Operation manual](docs/betriebshandbuch.md)
- [Technical documentation](docs/technischeDokumentation)
- [Glossary](docs/glossar.md)

## Contact

- Issues and discussions: [ims.project.shuttercontrol](https://github.com/gbssg/ims.project.shuttercontrol)
- Original maintainer: [@Basti8D](https://github.com/Basti8D)