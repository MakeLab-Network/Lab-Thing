
//#include <ESP8266WiFi.h>

#include <LabThing.h>


/*
   these urls should be accecible trough wifi network, although some routers Oppose...
   available URLs: (replace ID with your device's id)

   led -- http://lab_thing_ID.local/4/cmd/write?val=0&duration=1000 // try this to turn on built in led for 1000 millis...
   wifi settings -- http://lab_thing_ID.local/wifi // configure wifi settings
   OTA -- http://lab_thing_ID.local/firamware_update // press ctrl+alt+s then upload the bin file to web page (saved in sketch directory)

*/

#define AP_PASSWORD "Makelabthings!"
#define OTA_AUTH_USER_NAME "admin"
#define OTA_AUTH_PASSWORD "Makelabthings!"

//IPAddress staticIP(10, 0, 0, 65);
//IPAddress gateway(10, 0, 0, 1);
//IPAddress subnet(255, 255, 255, 0);


void setup() {
  Serial.begin(115200);
  LabThing.begin(AP_PASSWORD, OTA_AUTH_USER_NAME, OTA_AUTH_PASSWORD);
//  LabThing.wifiStatic(staticIP, gateway, subnet);
  pinMode(D4, OUTPUT);

}
void loop() {
  LabThing.run();

  digitalWrite(D4, millis() % 500 > 250);

}
