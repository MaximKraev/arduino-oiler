#include "main.h"

void setup() {
  DEBUG_SETUP
  DEBUG_PRINTLN("Setup")
  oilerSetup();
}

void loop() {
  oilerCheck();
}
