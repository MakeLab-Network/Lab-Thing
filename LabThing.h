/**
 * @file       labthing.h
 * @author     Yuval Dimri
 * @license    This project is released under the MIT License (MIT)?
 * @copyright  Copyright (c) 2022 Yuval Dimri
 * @date       march 2022
 * @brief
 *
 */

#ifndef LAB_THING_H
#define LAB_THING_H

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#include "Arduino.h"
#include <DNSServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <uri/UriBraces.h>

// labthing prints //
#ifdef LAB_THING_SERIAL
#define USE_SERIAL true
#else
#define USE_SERIAL false
#endif

#ifndef APSSID
#define APSSID "lab_thing_DEFAULT"
#define APPSK "12345678"
#endif

#define SERVER_PATH_OTA_UPDATE "/firmware_update"
#define OTA_UPDATE_USERNAME "admin"
#define OTA_UPDATE_PASSWORD "admin"

#define APSSID "lab_thing_default"

#define LONG_LIMIT_MAX 2147483647

extern char softAP_ssid[30];
extern char softAP_password[30];
extern char ssid[33];
extern char password[65];
extern int deviceId;
extern String myHostname;
extern bool wifiStaticConnection;
extern IPAddress WIFI_local_ip;
extern IPAddress WIFI_gateway;
extern IPAddress WIFI_subnet;

extern boolean reconnect;
extern unsigned long lastConnectTry;
extern unsigned int status;

extern long digitalPinsNextActionsTimes[9];
extern bool digitalPinsNextActionsValues[9];
extern long digitalPinsNearestActionTime;
extern bool nextActionValue;
extern byte nextPinForAction;
extern ESP8266WebServer server;

extern boolean isIp(String str);
extern String toStringIp(IPAddress ip);

extern DNSServer dnsServer;
#define DNS_PORT 53
typedef void (*voidFuncPtr)();
// #define SERVER_COSTUM_URL server.on

extern void GPIOCmdWrite();
extern void handleNotFound();
extern void handleWifiSave();
extern void handleWifiSettingsPage();
extern void startAP(const char *apPass);
extern void httpServerSetup(const char *otaUpdateUsername, const char *otaUpdatePassword);
extern void saveCredentials();
extern void loadCredentials();
extern void handleWifiConnection();
extern void handleGPIO();

class LabThingClass {
public:
  void begin(const char *apPass, const char *otaUpdateUsername, const char *otaUpdatePassword) {
    loadCredentials();
    startAP(apPass);
    httpServerSetup(otaUpdateUsername, otaUpdatePassword);
  }
  void wifiStatic(IPAddress local_ip, IPAddress gateway, IPAddress subnet) {
    wifiStaticConnection = 1;
    WIFI_local_ip = local_ip;
    WIFI_gateway = gateway;
    WIFI_subnet = subnet;
  }

  unsigned int run() {
    unsigned int s = handleWifiConnection();
    handleGPIO();
    return s;
  }
};

extern LabThingClass LabThing;

#endif