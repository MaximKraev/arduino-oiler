/*
 * led.cpp
 *
 *  Created on: 19 Apr 2017
 *      Author: mkraev
 */

#include "led.h"

static TimedAction *ledInterval;
static LED currentState = LED::INIT;
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
    case LED::INIT:
      LED_INIT
      break;
    case LED::NO_FIX:
      LED_NO_FIX
      break;
    case LED::FIX:
      LED_FIX
      break;
    case LED::NO_FIX_FALLBACK:
      LED_NO_FIX_FAILBACK
      break;
    case LED::FAILURE:
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


void setBlinksState(LED state) {
  DEBUG_PRINT("setBlinksState: ");
  DEBUG_PRINTLN(state);

  currentState = state;
}
