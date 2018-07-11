/*
 * led.cpp
 *
 *  Created on: 19 Apr 2017
 *      Author: mkraev
 */

#include "led.h"

//static TimedAction *ledInterval;
static LED currentState = LED::INIT;
static LED overrideState = LED::INIT;

void ledCheck() {
  //ledInterval->check();
}

static void setLed(int led, bool value) {
  int status = value ? LED_ON: LED_OFF;
  digitalWrite(led, status);
}


static void led(bool r, bool g, bool b) {
  setLed(LED_RED, r);
  setLed(LED_GREEN, g);
  setLed(LED_BLUE, b);
}

static void activate() {
  LED state = currentState;
  if (overrideState != LED::INIT) {
    state = overrideState;
  }
  switch (state)
  {
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
  case LED::PUMP_ACTIVE:
    LED_PUMP
    break;
    }

}


void ledSetup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
 // ledInterval = new TimedAction(LED_CYCLE_INTERVAL, &activate);
}


void setBlinksState(LED state) {
  DEBUG_PRINT("setBlinksState: ");
  DEBUG_PRINTLN(state);

  currentState = state;
  activate();
}

void setPriorityBlinksState(LED state) {
  DEBUG_PRINT("setPriorityBlinksState: ");
  DEBUG_PRINTLN(state);

  overrideState = state;
  activate();
}

void offPriorityBlinksState() {
  DEBUG_PRINTLN("offPriorityBlinksState: ");
  overrideState = LED::INIT;
  activate();
}

