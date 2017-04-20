#include "pump.h"

TimedAction *pumpingAction;

static void pumpOn() {
  DEBUG_PRINTLN("pumpOn");
  digitalWrite(PUMP, LOW);
}

static void pumpOff() {
  DEBUG_PRINTLN("pumpOff");
  digitalWrite(PUMP, HIGH);
}

void setupPump() {
  pinMode(PUMP, OUTPUT);
  pumpOff();
  pumpingAction = new TimedAction(500, &pumpCheck);
  pumpingAction->disable();
}

void pumpCheck() {
  pumpingAction->check();
}

void pumpStart() {
  pumpingAction->enable();
}

void pumpEnd() {
  pumpingAction->disable();
}

void dropPump(int delayMs) {
  DEBUG_PRINTLN("dropPump");
  pumpOn();
  delay(delayMs);
  pumpOff();
}
