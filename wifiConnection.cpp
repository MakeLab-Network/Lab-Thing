#include "lab-thing.h"
char softAP_ssid[] = APSSID;
char softAP_password[];
unsigned long lastConnectTry = 0;
unsigned int status = WL_IDLE_STATUS;
char ssid[33] = "";
char password[65] = "";
bool wifiStaticConnection = 0;
int deviceId = 0;

IPAddress WIFI_local_ip(0, 0, 0, 0);
IPAddress WIFI_gateway(0, 0, 0, 0);
IPAddress WIFI_subnet(0, 0, 0, 0);

boolean reconnect = 1; // 1 to connect on startup.
String myHostname = "lab_thing_default";

DNSServer dnsServer;

void connectToWifi()
{
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  int connRes = WiFi.waitForConnectResult();
  Serial.print("connRes: ");
  Serial.println(connRes);
}

void connectToWifiStatic()
{
  Serial.printf("Connecting with static IP to %s ", ssid);
  WiFi.config(WIFI_local_ip, WIFI_gateway, WIFI_subnet);
  WiFi.begin(ssid, password);
  int connRes = WiFi.waitForConnectResult();
  Serial.print("connRes: ");
  Serial.println(connRes);
}

void LabThingClass::startAP(const char *apPass)
{
  IPAddress apIP(172, 217, 28, 1);
  IPAddress netMsk(255, 255, 255, 0);

  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid, apPass);
  delay(500); // Without delay I've seen the IP address blank
  if (USE_SERIAL)
  {
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
  }
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
}

void LabThingClass::handleWifiConnection()
{
  if (reconnect)
  {
    Serial.println("Connect requested");
    reconnect = false;
    if (wifiStaticConnection)
      connectToWifiStatic();
    else
      connectToWifi();
    lastConnectTry = millis();
  }

  {
    unsigned int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 60000))
    {
      /* If WLAN disconnected and idle try to connect */
      /* Don't set retry time too low as retry interfere the softAP operation */
      reconnect = true;
    }
    if (status != s)
    { // WLAN status change
      Serial.print("Status: ");
      Serial.println(s);
      status = s;
      if (s == WL_CONNECTED)
      {
        /* Just connected to WLAN */
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        // Setup MDNS responder
        char hostNameTMP[60];
        myHostname.toCharArray(hostNameTMP, sizeof(hostNameTMP) - 1);
        Serial.printf("mDNS hostname: %s \n", myHostname);
        Serial.println(myHostname);
        if (!MDNS.begin(myHostname))
        {
          Serial.println("Error setting up MDNS responder!");
        }
        else
        {
          Serial.println("mDNS responder started");
          // Add service to MDNS-SD
          MDNS.addService("http", "tcp", 80);
        }
      }
      else if (s == WL_NO_SSID_AVAIL)
      {
        WiFi.disconnect();
        Serial.println("disconnecting from wifi");
      }
    }
    if (s == WL_CONNECTED)
    {
      MDNS.update();
    }
  }
  // Do work:

  // DNS
  dnsServer.processNextRequest();
  // HTTP
  server.handleClient();
}

/* Is this an IP? */
boolean isIp(String str)
{
  for (size_t i = 0; i < str.length(); i++)
  {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9'))
    {
      return false;
    }
  }
  return true;
}

/** IP to String? */
String toStringIp(IPAddress ip)
{
  String res = "";
  for (int i = 0; i < 3; i++)
  {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
