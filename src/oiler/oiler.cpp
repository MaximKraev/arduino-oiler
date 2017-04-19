#include "oiler.h"

float distance = 0;
bool pumpButtonStatus = false;

bool isRain = false;

float activateDistance = PUMP_ACTIVATE_DISTANCE;

static bool onRainStateChange(bool isRain) {
  activateDistance =
      (isRain) ? PUMP_ACTIVATE_DISTANCE * RAIN_FIX : PUMP_ACTIVATE_DISTANCE;
  return true;
}

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
    pumpOn();
    pumpButtonStatus = true;
  }

  if (pumpButtonStatus && !isPressed) {
    pumpOff();
    pumpButtonStatus = false;
  }
}

static void distanceReached() {
  dropPump(PUMP_TICK_MS);
}

static bool gpsCallback(float range) {

  if (range > RANGE_MIN_DISTANCE && range < RANGE_MAX_DISTANCE) {
    distance += range;
  }

  DEBUG_PRINT(F("Range: "));
  DEBUG_PRINT(range * 1000);
  DEBUG_PRINT("/");
  DEBUG_PRINT(RANGE_MIN_DISTANCE*1000);
  DEBUG_PRINTLN(F(" m"));
  DEBUG_PRINT(F("Distance: "));
  DEBUG_PRINT(distance * 1000);
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
  rainSensorCheck();
}

static bool onFixChange(bool hasFix) {
  if (hasFix) {
    DEBUG_PRINTLN("Got Fix");
    setBlinksState(LED_FIX);
  } else {
    DEBUG_PRINTLN("Lost Fix");
    setBlinksState(LED_NO_FIX);
  }

  return true;
}

TCallbackFloat distanceCallback;
TCallbackBool rainCallback;
TCallbackBool fixCallback;

void oilerSetup() {
  ledSetup();
  setBlinksState(LED_INIT);

  //Pump
  setupPump();
  setupPumpButton();


  rainCallback.SetCallback(&onRainStateChange);
  rainSensorSetup(rainCallback);

  distanceCallback.SetCallback(&gpsCallback);
  fixCallback.SetCallback(&onFixChange);
  GPSSetup(distanceCallback, fixCallback);

}
