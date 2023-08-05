#include "lab-thing.h"

// ota //
const char *otaUpdatePath = SERVER_PATH_OTA_UPDATE;

ESP8266HTTPUpdateServer httpUpdater;
// ota //

ESP8266WebServer server = ESP8266WebServer(80);

void LabThingClass::httpServerSetup(const char *otaUpdateUsername, const char *otaUpdatePassword)
{
  // Start webserver

  // ota updater setup to respond on http server
  httpUpdater.setup(&server, otaUpdatePath, otaUpdateUsername, otaUpdatePassword);

  server.on("/", []()
            {
    Serial.println("'/' requested");
    server.send(200, "text/plain", "MakeLab Device with ID: " + String(deviceId)); });
  server.on("/wifi", handleWifiSettingsPage);
  server.on("/wifisave", handleWifiSave);
  server.on("/generate_204", handleWifiSettingsPage); // Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleWifiSettingsPage);       // Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.onNotFound(handleNotFound);
  server.on(UriBraces("/{}/cmd/write"), GPIOCmdWrite);

  server.begin();
}
