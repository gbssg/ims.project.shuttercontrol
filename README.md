# ShutterControl

## Project description

The project ShutterControl is a control for shutters that controls two motors in the standard configuration. These Motors can be controlled through an API or Buttons. It allows the control of the shutters from the desks and technically everywhere in the same Network.

## Starting point

The Room had two shutters with their respective switch. There was no way to control them from the desks. To control the shutters someone had to stand up and walk to the switches or the person next to the switches was asked to open/close them.

## Vision

The Project should allow the users to control the shutters from every desk so that we can save some time. Additionally the person next to the switches doesn't have to control the shutters for the others. This should be achieved with an ESP32 that is connected to the Internet and has some physical control for people without API access.

## Getting Started

- Install the VisualStudio extension for [PlatformIO](vscode:extension/platformio.platformio-ide)
- Create the file secrets.hin the folder `plattformIO\shuttercontrol_v4\lib\secrets\` with this Template: `plattformIO\shuttercontrol_v4\lib\secrets\template.secrets.h`
  - If the API-key is not set there is an possibility of an crash or unauthorized access. 
- Upload the Code with PlatformIO

## Further reading

- [Operation manual](docs/betriebshandbuch.md)
- [Technical Documentation](docs/technischeDokumentation)
- [Glossary](docs/glossar.md)

## Contact

- Issues and discussions: [ims.project.shuttercontrol](https://github.com/gbssg/ims.project.shuttercontrol)
- Original maintainer: [@Basti8D](https://github.com/Basti8D)