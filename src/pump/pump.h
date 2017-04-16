#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>
#include <TimedAction.h>
#include "debug.h"
#include "consts.h"

void dropPump(int delayMs);
void setupPump();
void pumpOn();
void pumpOff();
#endif
