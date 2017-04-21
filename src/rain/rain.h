#ifndef RAIN_H
#define RAIN_H

#include "include.h"
#include "callback/callback.h"
#include "TimedAction.h"

void rainSensorSetup(TCallbackBool &stateChangeCallback);
void rainSensorCheck();
#endif
