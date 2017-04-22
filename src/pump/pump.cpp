#include "pump.h"

static TimedAction *pumpingAction;

static void pumpOn() {
  DEBUG_PRINTLN("pumpOn");
  digitalWrite(PUMP, LOW);
}

static void pumpOff() {
  DEBUG_PRINTLN("pumpOff");
  digitalWrite(PUMP, HIGH);
}

static void pumpActivate() {
  dropPump(PUMP_BUTTON_ACTIVE);
}

void setupPump() {
  pinMode(PUMP, OUTPUT);
  pumpOff();
  pumpingAction = new TimedAction(PUMP_BUTTON_INTERVAL, &pumpActivate);
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
