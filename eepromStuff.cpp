#include "lab-thing.h"
#include <EEPROM.h>

/* Load credentials from EEPROM */
void LabThingClass::loadCredentials()
{
  EEPROM.begin(512);
  EEPROM.get(0, ssid);
  EEPROM.get(0 + sizeof(ssid), password);
  EEPROM.get(0 + sizeof(ssid) + sizeof(password), deviceId);
  EEPROM.get(0 + sizeof(ssid) + sizeof(password) + sizeof(deviceId), softAP_ssid);
  myHostname = String(softAP_ssid);
  char ok[2 + 1];
  EEPROM.get(0 + sizeof(ssid) + sizeof(password) + sizeof(deviceId) + sizeof(softAP_ssid), ok);
  EEPROM.end();
  if (String(ok) != String("OK"))
  {
    Serial.println("eeprom reding faulty\n");
    ssid[0] = 0;
    password[0] = 0;
    myHostname = APSSID;
    myHostname.toCharArray(softAP_ssid, sizeof(softAP_ssid) - 1); // let ap ssid be the hostname
    deviceId = -1;
  }
  Serial.printf("Recovered credentials: ssid: %s. password: %s.\nsoftAP_ssid: %s \ndevice id: %d \n", ssid, password, softAP_ssid, deviceId);
}

/** Store credentials to EEPROM */
void saveCredentials()
{
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0 + sizeof(ssid), password);
  EEPROM.put(0 + sizeof(ssid) + sizeof(password), deviceId);
  EEPROM.put(0 + sizeof(ssid) + sizeof(password) + sizeof(deviceId), softAP_ssid);
  char ok[2 + 1] = "OK";
  EEPROM.put(0 + sizeof(ssid) + sizeof(password) + sizeof(deviceId) + sizeof(softAP_ssid), ok);
  EEPROM.commit();
  EEPROM.end();
  Serial.printf("Saved credentials to eeprom: ssid: %s. password: %s.\nsoftAP_ssid: %s \ndevice id: %d \n", ssid, password, softAP_ssid, deviceId);
}
