#ifdef ARDUINO_ESP8266_NODEMCU
#ifndef OTA_H
#define OTA_H

#include "include.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>

void otaSetup();
void otaLoop();

#endif
#endif