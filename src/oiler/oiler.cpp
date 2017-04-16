#include "oiler.h"

float distance = 0;
bool pumpButtonStatus = false;

bool isRain = false;

float activateDistance = PUMP_ACTIVATE_DISTANCE;

bool onRainStateChange(void *Param) {
  bool isRain = *(bool*) Param;
  activateDistance = (isRain) ? PUMP_ACTIVATE_DISTANCE * RAIN_FIX : PUMP_ACTIVATE_DISTANCE;
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

  DEBUG_PORT.print( F("Range: ") );
  DEBUG_PORT.print( range*1000 );
  DEBUG_PORT.print("/");
  DEBUG_PORT.print(RANGE_MIN_DISTANCE*1000);
  DEBUG_PORT.println( F(" m") );
  DEBUG_PORT.print( F("Distance: ") );
  DEBUG_PORT.print( distance*1000 );
  DEBUG_PORT.println( F(" m") );

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
}

TCallback distanceCallback;

void oilerSetup() {
  setupPump();
  setupPumpButton();
  distanceCallback.SetCallback(&gpsCallback);
  GPSSetup(distanceCallback);
}
