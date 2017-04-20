/*
 * led.cpp
 *
 *  Created on: 19 Apr 2017
 *      Author: mkraev
 */

#include "led.h"

TimedAction *ledInterval;
TimedAction *ledBlinks;

int blinksPerSecond = LED_INIT; //default 1 init state

int currentBlink = 0;
int currentStatus = false;

void ledCheck() {
  ledBlinks->check();
  ledInterval->check();
}


static void activateLed() {
  digitalWrite(STATUS_LED, HIGH);
}

static void deactivateLed() {
  digitalWrite(STATUS_LED, LOW);
}

static void blink() {
  if (currentStatus) {
    activateLed();
  } else {
    deactivateLed();
    currentBlink++;
    if (currentBlink >= blinksPerSecond) {
      ledBlinks->disable();
    }
  }
  currentStatus = !currentStatus;
}


void setBlinksState(int blinks) {
  blinksPerSecond = blinks;
}

static void activate() {
  currentBlink = 0;
  ledBlinks->enable();
}

void ledSetup() {
  ledBlinks = new TimedAction(LED_BLINK_INTERVAL, &blink);
  ledBlinks->disable();
  ledInterval = new TimedAction(LED_CYCLE_INTERVAL, &activate);
  ledInterval->enable();
}


