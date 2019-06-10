#ifndef PUMP_H
#define PUMP_H

#include "include.h"
#include <TimedAction.h>
#include "led/led.h"

void dropPump(int delayMs);
void setupPump();
void pumpStart();
void pumpEnd();
void pumpCheck();

#endif
