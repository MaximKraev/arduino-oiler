#include "pump.h"

void pumpOn() {
  DEBUG_PRINTLN("pumpOn");
  digitalWrite(PUMP, LOW);
}

void pumpOff() {
  DEBUG_PRINTLN("pumpOff");
  digitalWrite(PUMP, HIGH);
}

void setupPump() {
  pinMode(PUMP, OUTPUT);
  pumpOff();
}

void dropPump(int delayMs) {
  DEBUG_PRINTLN("dropPump");
  pumpOn();
  delay(delayMs);
  pumpOff();
}