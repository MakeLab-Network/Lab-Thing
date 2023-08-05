#include "lab-thing.h"
/*
 * 1. add this program code to your code.
 * 2. your device should now create a wifi Access Point when started.
 * 3. connect to this AP using the AP_PASSWORD defined below.
 * 4. go to the config page (using the url below) and configure the local wifi credentials and a device ID
 * 5. restart the esp (the credentials and ID are saved in the EEPROM)
 * 6. you can now control this esp GPIO's with the url's below, from any device connected to the same wifi network.

   led -- http://lab_thing_ID.local/4/cmd/write?val=0&duration=1000 // try this to turn on built in led for 1000 millis...
   wifi settings -- http://lab_thing_ID.local/wifi // configure wifi settings
   OTA -- http://lab_thing_ID.local/firamware_update // press ctrl+alt+s then upload the bin file to web page (saved in sketch directory)

*/

#define AP_PASSWORD "12345678"
#define OTA_AUTH_USER_NAME "admin"
#define OTA_AUTH_PASSWORD "admin"

void setup() {
  Serial.begin(115200);
  LabThing.begin(AP_PASSWORD, OTA_AUTH_USER_NAME, OTA_AUTH_PASSWORD);
}

void loop() {  // dont use delay here
  LabThing.run();
}
