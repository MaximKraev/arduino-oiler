#include "rain.h"

// Checks for RAIN_CHECK_INTERVAL,

static cCallbackBool *_stateChangeCallback;
static TimedAction *rainCheckTimer;

static bool isCurrentlyRain = false;

void rainSensorSetup(TCallbackBool *stateChangeCallback) {
  _stateChangeCallback = stateChangeCallback;

}

static bool getIsRain() {
  return false; // no sensor yet
}

static void onCheck() {
  static bool rain = getIsRain();
  if (rain && !isCurrentlyRain) {
    isCurrentlyRain = true;
    _stateChangeCallback->Execute(true);
  } else if (!rain && isCurrentlyRain) {
    isCurrentlyRain = true;
    _stateChangeCallback->Execute(false);
  }
}

void rainSensorCheck() {
  rainCheckTimer = new TimedAction(4000, onCheck);
}
