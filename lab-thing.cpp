#include "LabThing.h"

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

// private methods
void LabThing::loadCredentials()
{
    // logic for loading credentials goes here
}

void LabThing::startAP(const char *apPass)
{
    // logic for starting the AP goes here
}

void LabThing::httpServerSetup(const char *otaUpdateUsername, const char *otaUpdatePassword)
{
    // logic for setting up the server goes here
}

void LabThing::handleWifiConnection()
{
    // logic for handling WIFI connection goes here
}

void LabThing::handleGPIO()
{
    // logic for handling GPIO goes here
}
