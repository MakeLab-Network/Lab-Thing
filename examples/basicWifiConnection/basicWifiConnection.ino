#include <lab-thing.h>

/*
   these urls should be accecible trough wifi network, although some routers Oppose...
   available URLs: (replace ID with your device's id)

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

void loop() { // dont use delay here
  LabThing.run();
}
