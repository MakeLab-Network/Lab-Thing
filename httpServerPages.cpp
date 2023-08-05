#include "lab-thing.h"

// void costumUrlHelperFunc(voidFuncPtr handler) {
//   server.client().setNoDelay(true); // disables Nagle's algorithm. everything is faster
//   server.send(200, "text/plain", "");
//   handler();
// }
void handleWifiSettingsPage() {
  server.client().setNoDelay(true);
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  String Page;
  Page += F(
      "<!DOCTYPE html><html lang='en'><head>"
      "<meta name='viewport' content='width=device-width'>"
      "<title>CaptivePortal</title></head><body>"
      "<h1>Wifi config</h1>");
  Page +=
      String(F(
          "\r\n<br />"
          "<table><tr><th align='left'>SoftAP config</th></tr>"
          "<tr><td>SSID ")) +
      String(softAP_ssid) +
      F("</td></tr>"
        "<tr><td>IP ") +
      toStringIp(WiFi.softAPIP()) +
      F("</td></tr>"
        "</table>"
        "\r\n<br />"
        "<table><tr><th align='left'>WLAN config</th></tr>"
        "<tr><td>SSID ") +
      String(ssid) +
      F("</td></tr>"
        "<tr><td>IP ") +
      toStringIp(WiFi.localIP()) +
      F("</td></tr>"
        "</table>"
        "\r\n<br />"
        "<table><tr><th align='left'>WLAN list (refresh if any missing)</th></tr>");
  if (USE_SERIAL)
    Serial.println("scan start");
  int n = WiFi.scanNetworks();
  if (USE_SERIAL)
    Serial.println("scan done");
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      Page += String(F("\r\n<tr><td>SSID ")) + WiFi.SSID(i) + ((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? F(" ") : F(" *")) + F(" (") + WiFi.RSSI(i) + F(")</td></tr>");
    }
  } else {
    Page += F("<tr><td>No WLAN found</td></tr>");
  }
  Page += F(
      "</table>"
      "\r\n<br /><form method='POST' action='wifisave'><h4>Connect to network:</h4>"
      "<input type='text' placeholder='network' name='ssid'/>"
      "<br /><input type='text' placeholder='password' name='pass'/>"
      "<br /><input type='text' placeholder='device ID' name='device_id' required/>"
      "<br /><input type='submit' value='Connect/Disconnect'/></form>"
      "<h1>reset device to chage AP ssid!! (hostname will change.)</h1>"
      "</body></html>");
  server.send(200, "text/html", Page);
  server.client().stop(); // Stop is needed because we sent no content length
}

void handleWifiSave() {
  if (USE_SERIAL)
    Serial.println("wifi save");
  server.arg("ssid").toCharArray(ssid, sizeof(ssid) - 1);
  server.arg("pass").toCharArray(password, sizeof(password) - 1);
  deviceId = server.arg("device_id").toInt();
  myHostname = "lab_thing_" + String(deviceId);
  myHostname.toCharArray(softAP_ssid, sizeof(softAP_ssid) - 1); // let ap ssid be the hostname

  server.sendHeader("Location", "wifi", true);
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.client().stop();             // Stop is needed because we sent no content length
  saveCredentials();
  reconnect = strlen(ssid) > 0; // Request WLAN connect with new credentials if there is a SSID
}

void handleNotFound() {
  String message = F("File Not Found\n\n");
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");

  for (uint8_t i = 0; i < server.args(); i++) {
    message += String(F(" ")) + server.argName(i) + F(": ") + server.arg(i) + F("\n");
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(404, "text/plain", message);
}
