#include "lab-thing.h"

void LabThing::begin(const char *apPass, const char *otaUpdateUsername, const char *otaUpdatePassword)
{
    loadCredentials();
    startAP(apPass);
    httpServerSetup(otaUpdateUsername, otaUpdatePassword);
}

void LabThing::wifiStatic(IPAddress local_ip, IPAddress gateway, IPAddress subnet)
{
    wifiStaticConnection = 1;
    WIFI_local_ip = local_ip;
    WIFI_gateway = gateway;
    WIFI_subnet = subnet;
}

ESP8266WebServer &LabThing::getServer()
{
    return server;
}

void LabThing::run()
{
    handleWifiConnection();
    handleGPIO();
}
