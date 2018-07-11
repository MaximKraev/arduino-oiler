#ifdef ARDUINO_ESP8266_NODEMCU
#include "ota.h"

bool otaEnabled = false;
bool wifiOff = false;

void enableOta()
{
  if (otaEnabled) {
    return;
  }
  DEBUG_PRINTLN("enableOTA");

  otaEnabled = true;
  ArduinoOTA.onStart([]() {
    DEBUG_PRINTLN(F("OTA on start"));

    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    DEBUG_PRINTLN("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    DEBUG_PRINTLN("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    DEBUG_PRINTF("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    DEBUG_PRINTF("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      DEBUG_PRINTLN("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      DEBUG_PRINTLN("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      DEBUG_PRINTLN("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      DEBUG_PRINTLN("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      DEBUG_PRINTLN("End Failed");
    }
  });
  ArduinoOTA.begin();
  DEBUG_PRINTLN("Ready");
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINTLN(WiFi.softAPIP());
}

void onConnect() {
  DEBUG_PRINTLN("onConnect");
  enableOta();
}

// crashing
void stopWifi() {
  wifiOff = true;
  DEBUG_PRINTLN("stopWifi");
  WiFi.mode(WIFI_OFF);
  DEBUG_PRINTLN("Sleep begin");
  WiFi.forceSleepBegin();
  digitalWrite(2, LOW);
}

void WiFiEvent(WiFiEvent_t event) {
  DEBUG_PRINT("WifiEvent: ");
  DEBUG_PRINTLN(event);
  if (event == WIFI_EVENT_SOFTAPMODE_STACONNECTED) {
    onConnect();
  }
}

void initWifi() {
  DEBUG_PRINTLN("initWifi");
  digitalWrite(2, HIGH);

  WiFi.persistent(false);
  WiFi.onEvent(WiFiEvent, WIFI_EVENT_ANY);
  WiFi.softAP(OILER_SSID, OILER_PASSWORD);
}

void otaSetup() {
  initWifi();
}

void otaLoop() {
  if (!otaEnabled && !wifiOff && millis() > WIFI_OTA_WAIT) {
    stopWifi();
  } else if (otaEnabled) {
    ArduinoOTA.handle();
  }
}
#endif