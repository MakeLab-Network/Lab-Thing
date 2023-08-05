Lab-Thing Library for ESP8266
version coverage license

Lab-Thing is a powerful C++ library for ESP8266 devices that enables seamless communication between these devices. With Lab-Thing, any ESP8266 device can control the pins of any other ESP866 device running the same library.

Features
Easy Communication: Lab-Thing allows ESP8266 devices to easily communicate with each other.
Pin Control: This feature allows any ESP8266 device to control the pins of another ESP8266 device running Lab-Thing.
Installation
To install the Lab-Thing library, you can download it from this repository and add it to your Arduino IDE. Follow these steps:

Download the library from this repository.
In the Arduino IDE, navigate to Sketch -> Include Library -> Add .ZIP Library.
At the top of the sketch, include the library.
Dependencies
Before you start using the Lab-Thing library, make sure the following dependencies are installed:

Add dependencies here...
Usage
To use the Lab-Thing library in your sketch, include it at the top:

#include "Lab-Thing.h"
Then, you can call the functions provided by the library. An example would be:

//Add usage example here
Examples
You can find examples of how to use this library in the examples folder of this repository.

Troubleshooting
If you experience any issues while using this library, please open an issue in this repository.

Contributing
Contributions to this library are welcome. If you want to contribute, please make a pull request.

License
This library is released under the MIT License. See the included LICENSE file for more details.

Please note that it is your responsibility to comply with the hardware limitations of your device and use this library responsibly.

(currently only wemos D1 mini is supported and tested...) <br><br>
configure wifi credentials with a web server gui by Access point connection.<br>
give each module a unique ID, and access it's web server fuctions over `http://lab_thing_<ID>/` (on lan network) 
