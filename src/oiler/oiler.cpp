#include "oiler.h"

static float distance = 0;
static bool pumpButtonStatus = false;

static float activateDistance = PUMP_ACTIVATE_DISTANCE;

static TimedAction * noFixFailbackTimer;
static TimedAction * noFixTimer;

//static bool onRainStateChange(bool _isRain) {
//  DEBUG_PRINT(F("onRainStateChange "));
//  DEBUG_PRINTLN(_isRain);
//
//  static unsigned long noFixFailbackInterval = NO_FIX_INTERVAL
//      * ((_isRain) ? RAIN_FIX : 1);
//  noFixFailbackTimer->setInterval(noFixFailbackInterval);
//
//  activateDistance =
//      (_isRain) ? PUMP_ACTIVATE_DISTANCE * RAIN_FIX : PUMP_ACTIVATE_DISTANCE;
//
//  return true;
//}

static void setupPumpButton() {
  pinMode(PUMP_BUTTON, INPUT);
  digitalWrite(PUMP_BUTTON, HIGH);
}

static bool isPumpButtonPressed() {
  return !digitalRead(PUMP_BUTTON);
}

static void pumpButtonCheck() {
  bool isPressed = isPumpButtonPressed();

  if (!pumpButtonStatus && isPressed) {
    pumpStart();
    pumpButtonStatus = true;
  }

  if (pumpButtonStatus && !isPressed) {
    pumpEnd();
    pumpButtonStatus = false;
  }
}

static void noFixFailback(bool activate) {
  noFixFailbackTimer->reset();
  noFixTimer->reset();
  noFixTimer->disable();
  if (activate) {
    noFixFailbackTimer->enable();
  } else {
    DEBUG_PRINTLN(F("noFixFailback disable"));
    noFixFailbackTimer->disable();
  }
}

static void distanceReached() {
  dropPump(PUMP_TICK_MS);
}

static void noFixIntervalReached() {
  DEBUG_PRINTLN(F("noFixIntervalReached"));
  setBlinksState(LED::NO_FIX_FALLBACK);
  noFixFailback(true);
}

static void noFixFailbackSetup() {
  noFixFailbackTimer = new TimedAction(NO_FIX_INTERVAL, distanceReached);
  noFixTimer = new TimedAction(NO_FIX_START_TIMEOUT, noFixIntervalReached);
}

static void noFixTimerCheck() {
  noFixTimer->check();
  noFixFailbackTimer->check();
  noFixFailback(false);
}

static bool gpsCallback(float range) {

  if (range < RANGE_MIN_DISTANCE || range > RANGE_MAX_DISTANCE) {
    return false;
  }

  distance += range;

  DEBUG_PRINT(F("Distance: "));
  DEBUG_PRINT(distance);
  DEBUG_PRINTLN(F(" m"));

  if (activateDistance < distance) {
    distance -= activateDistance;

    if (activateDistance < distance) { // reset distance to prevent multiple triggers
      distance = 0;
    }
    distanceReached();
  }
  return true;
}

void oilerCheck() {
  GPSCheck();
  ledCheck();
  pumpButtonCheck();
  pumpCheck();
//  rainSensorCheck();
  noFixTimerCheck();
}

static bool onFixChange(bool hasFix) {
  if (hasFix) {
    noFixTimer->setInterval(NO_FIX_TIMEOUT);
    DEBUG_PRINTLN("Got Fix");
    setBlinksState(LED::FIX);
    noFixFailback(false);
  } else {
    DEBUG_PRINTLN("Lost Fix");
    setBlinksState(LED::NO_FIX);
    noFixTimer->reset();
    noFixTimer->enable();
  }
  return true;
}

static TCallbackFloat *distanceCallback;
//static TCallbackBool *rainCallback;
static TCallbackBool *fixCallback;

void oilerSetup() {

  noFixFailbackSetup();

  ledSetup();
  setBlinksState(LED::INIT);

  //Pump
  setupPump();
  setupPumpButton();

//  rainCallback = new TCallbackBool(&onRainStateChange);
//  rainSensorSetup(rainCallback);

  distanceCallback = new TCallbackFloat(&gpsCallback);
  fixCallback = new TCallbackBool(&onFixChange);

  GPSSetup(distanceCallback, fixCallback);

}
