/*
 * led.cpp
 *
 *  Created on: 19 Apr 2017
 *      Author: mkraev
 */

#include "led.h"

static TimedAction *ledInterval;
static int currentState = LED::init;
static bool isOn = false;

void ledCheck() {
  ledInterval->check();
}

static void setLed(int led, bool value) {
  int status = value ? LED_ON: LED_OFF;
  analogWrite(led, status);
}


static void led(bool r, bool g, bool b, bool builtIn) {
  setLed(LED_RED, r);
  setLed(LED_GREEN, g);
  setLed(LED_BLUE, b);
  digitalWrite(LED_BUILTIN, builtIn);
}

static void activate() {
  if (isOn) {
    switch(currentState) {
    case LED::init:
      LED_INIT
      break;
    case LED::no_fix:
      LED_NO_FIX
      break;
    case LED::fix:
      LED_FIX
      break;
    case LED::no_fix_fallback:
      LED_NO_FIX_FAILBACK
      break;
    case LED::failure:
      LED_FAILURE
      break;
    }
  } else {
    LED_DISABLE
  }
  isOn = !isOn;
}


void ledSetup() {
  ledInterval = new TimedAction(LED_CYCLE_INTERVAL, &activate);
}


void setBlinksState(int state) {
  DEBUG_PRINT("setBlinksState: ");
  DEBUG_PRINTLN(state);

  currentState = state;
}
