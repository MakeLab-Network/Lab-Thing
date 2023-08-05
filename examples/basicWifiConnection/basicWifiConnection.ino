// Include the core Lab-Thing library
#include <lab-thing.h>

/**
 * This script allows your device to create a wifi Access Point (AP) on startup.
 * 
 * To use, follow the steps:
 * 1. Merge this script with your existing code.
 * 2. On startup, your esp device will create a WIFI AP (labthing_default). 
 * 3. Connect to this AP using the AP_PASSWORD (defined below).
 * 4. Go to the config page (URL mentioned below) to provide the local WiFi credentials and device ID.
 * 5. Restart the ESP8266. (This allows the EEPROM to save the credentials and ID).
 * 6. Your ESP GPIO's can now be controlled by the URL's below from any device on the wifi network. Enjoy!
 * 
 * URL Endpoints:
 * - Control LED: http://lab_thing_<ID>.local:30300/4/cmd/write?val=0&duration=1000 (Sets the built-in LED to HIGH for 1000 millis)
 * - WiFi Settings: http://lab_thing_<ID>.local:30300/wifi (Configure Wi-Fi settings)
 * - Firmware Updates (OTA): http://lab_thing_<ID>.local:30300/firmware_update (Press CTRL+ALT+S, then upload the .bin file located in the sketch directory)
 * note that the DNS can sometimes cause problems, if the above URL's does not work it is recommended using the device ip instead (printed to the serial monitor).
 */

// Constant definitions for WiFi Access Point and OTA Update Authentication
#define AP_PASSWORD        "12345678"
#define OTA_AUTH_USER_NAME "admin"
#define OTA_AUTH_PASSWORD  "admin" // CHANGE THIS!

void setup() 
{
  // Begin serial communication at a baudrate of 115200
  Serial.begin(115200);

  // Begin the Lab-Thing instance with the necessary credentials
  LabThing.begin(AP_PASSWORD, OTA_AUTH_USER_NAME, OTA_AUTH_PASSWORD);
}

void loop() 
{
  // Continously run the Lab-Thing library's functionalities
  // IMPORTANT: Do not use delay() here as it might interfere with the timing of LabThing functions
  LabThing.run();
}
