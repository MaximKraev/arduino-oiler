#ifndef RAIN_H
#define RAIN_H

#include "include.h"
#include "callback/callback.h"

void rainSensorSetup(TCallback &stateChangeCallback);
void rainSensorCheck();
#endif