#include "oiler.h"

float distance = 0;
bool pumpButtonStatus = false;

bool isRain = false;

float activateDistance = PUMP_ACTIVATE_DISTANCE;

bool onRainStateChange(void *Param) {
  bool isRain = *(bool*) Param;
  activateDistance = (isRain) ? PUMP_ACTIVATE_DISTANCE * RAIN_FIX : PUMP_ACTIVATE_DISTANCE;
  return true;
}

void setupPumpButton() {
  pinMode(PUMP_BUTTON, INPUT);
  digitalWrite(PUMP_BUTTON, HIGH);
}

bool isPumpButtonPressed()
{
  return !digitalRead(PUMP_BUTTON);
}

void pumpButtonCheck() {
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

void distanceReached() {
  dropPump(PUMP_TICK_MS);
}

bool gpsCallback(void *Param) {

  float range = *(float*) Param;
  if (range > RANGE_MIN_DISTANCE && range < RANGE_MAX_DISTANCE) {
    distance += range;
  }

  DEBUG_PRINT( F("Range: ") );
  DEBUG_PRINT( range*1000 );
  DEBUG_PRINT("/");
  DEBUG_PRINT(RANGE_MIN_DISTANCE*1000);
  DEBUG_PRINTLN( F(" m") );
  DEBUG_PRINT( F("Distance: ") );
  DEBUG_PRINT( distance*1000 );
  DEBUG_PRINTLN( F(" m") );

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
  pumpButtonCheck();
  rainSensorCheck();
}

bool onFixChange(void *Param) {
  bool hasFix = *(int*) Param;

  if (hasFix) {
    DEBUG_PRINTLN("Got Fix");
  } else {
    DEBUG_PRINTLN("Lost Fix");
  }

  return true;
}

TCallback distanceCallback;
TCallback rainCallback;
TCallback fixCallback;

void oilerSetup() {
  setupPump();
  setupPumpButton();
  rainCallback.SetCallback(&onRainStateChange);
  rainSensorSetup(rainCallback);

  distanceCallback.SetCallback(&gpsCallback);
  fixCallback.SetCallback(&onFixChange);
  GPSSetup(distanceCallback, fixCallback);
}
