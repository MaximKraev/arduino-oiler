#ifndef OILER_H
#define OILER_H
#include <Arduino.h>

#include "debug.h"
#include "consts.h"
#include "pump/pump.h"
#include "GPS/gps.h"
#include "callback/callback.h"

void oilerCheck();
void oilerSetup();
#endif