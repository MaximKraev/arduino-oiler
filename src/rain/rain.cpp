#include "rain.h"

// Checks for RAIN_CHECK_INTERVAL,

cCallbackBool *_stateChangeCallback;

void rainSensorSetup(TCallbackBool &stateChangeCallback) {
  _stateChangeCallback = &stateChangeCallback;

}

void rainSensorCheck() {

}