#include "rain.h"

// Checks for RAIN_CHECK_INTERVAL,

cCallback *_stateChangeCallback;

void rainSensorSetup(TCallback &stateChangeCallback) {
  _stateChangeCallback = &stateChangeCallback;

}

void rainSensorCheck() {

}