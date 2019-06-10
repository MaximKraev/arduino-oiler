#include "pump.h"

static TimedAction *pumpingAction;
static TimedAction *pumpActiveAction;

static void pumpOn() {
  DEBUG_PRINTLN("pumpOn");
  digitalWrite(PUMP, HIGH);
  setPriorityBlinksState(LED::PUMP_ACTIVE);
  pumpActiveAction->reset();
  pumpActiveAction->enable();
}

static void pumpOff() {
  DEBUG_PRINTLN("pumpOff");
  digitalWrite(PUMP, LOW);
  offPriorityBlinksState();
  pumpActiveAction->disable();
}

static void pumpActivate() {
  dropPump(PUMP_BUTTON_ACTIVE);
}

void setupPump() {
  pinMode(PUMP, OUTPUT);

  pumpingAction = new TimedAction(PUMP_BUTTON_INTERVAL, &pumpActivate);
  pumpingAction->disable();

  pumpActiveAction = new TimedAction(PUMP_TICK_MS, &pumpOff);
  pumpActiveAction->disable();
  pumpOff();

}

void pumpCheck() {
  pumpingAction->check();
  pumpActiveAction->check();
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
}
