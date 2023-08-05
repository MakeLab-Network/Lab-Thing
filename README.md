# Lab-Thing Library for ESP8266
[![version](https://img.shields.io/badge/version-1.0.0-brightgreen)](https://github.com/guyostfeld/Lab-Thing/)
![coverage](https://img.shields.io/badge/coverage-100%25-brightgreen)
![license](https://img.shields.io/badge/license-MIT-brightgreen)

Lab-Thing is a powerful C++ library for ESP8266 IOT devices.
With Lab-Thing, you can easly connect your esp device to the wifi network and control it's pins from your browser with simple urls / http requests.

## Features

- **WiFi Configuration Screen:** Provides an easy-to-use graphical user interface for configuring the WiFi connection for your ESP8266.
- **Pin Control:** you can control the GPIO pins of the esp from your phone/PC from the browser using a simple url.
- **Custom Commands:** can recieve custom commands from the web to execute custom functions.
- **OTA Update:** Offers Over-The-Air (OTA) functionality for updating your code on the ESP8266.

## Installation

To install the Lab-Thing library, you can download it from this repository and add it to your Arduino IDE. Follow these steps:

1. Download the library from this repository.
2. In the Arduino IDE, navigate to Sketch -> Include Library -> Add .ZIP Library.
3. At the top of the sketch, include the library.

## Dependencies

There are currently no needed dependencies.

## Code

To use the Lab-Thing library in your sketch, include it at the top:
#include "Lab-Thing.h"

in setup: 
LabThing.begin(AP_PASSWORD, OTA_AUTH_USER_NAME, OTA_AUTH_PASSWORD);

in loop:
LabThing.run(); // make sure this runs periodically and your program is not blocking.

and that's all you need! after a quick configuration (shown in the Usage section below) you can now send commands to this esp from your phone or PC!


other commands:

- LabThing.getServer().on("/hello", httpHello); // use once in setup. the function httpHello will be called when the string "hello" is given in the uri.
- LabThing.wifiStatic(staticIP, gateway, subnet); // configure static options.

## Usage
1. run the simple sketch as shown above, 
   the esp will create an AP named "LabThing".
   connect to it with AP_PASSWORD from your phone or PC,
2. go to - http://lab_thing_default.local/wifi to configure your device, 
   configure the local wifi credentials and assign an ID for your device,
   the wifi credentials and the device ID will be saved in the EEPROM, so you only need to configure your device once!
   - to access the configuration page again, go to  http://lab_thing_<id>.local/wifi
3. you can now control the esp using your phone or pc!
   connect to the same wifi network you configured for the device,
   and use the browser to control it's pins!
   e.g: http://lab_thing_ID.local/4/cmd/write?val=0&duration=1000 // try this to turn on built in led for 1000 millis.

## Examples

You can find examples of how to use this library in the `examples` folder of this repository.

## Troubleshooting

If you experience any issues while using this library, please open an issue in this repository and tell us!

## Contributing

Contributions to this library are welcome. If you want to contribute, please make a pull request. you are also encouraged to contact us directly!

## License

This library is released under the MakeLab License. Feel free to use it for any personal Makers project.

