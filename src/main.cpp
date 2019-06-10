#include "main.h"

void setup() {
  DEBUG_SETUP
  DEBUG_PRINTLN("Setup")
  #ifdef OTA_SUPPORTED
  otaSetup();
  #endif
  oilerSetup();
}

void loop() {
  #ifdef OTA_SUPPORTED
  otaLoop();
  #endif
  oilerCheck();
}
