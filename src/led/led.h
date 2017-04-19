/*
 * led.h
 *
 *  Created on: 19 Apr 2017
 *      Author: mkraev
 */

#ifndef SRC_LED_LED_H_
#define SRC_LED_LED_H_

#include "include.h"
#include <TimedAction.h>

#define LED_INIT 1
#define LED_NO_FIX 2
#define LED_FIX 3
#define LED_FAILURE 4

#define LED_CYCLE_INTERVAL 4000
#define LED_BLINK_INTERVAL 200

void ledCheck();
void ledSetup();
void setBlinksState(int blinks);

#endif /* SRC_LED_LED_H_ */
