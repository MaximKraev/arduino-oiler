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

#define LED_ON 250
#define LED_OFF 255

#define RGB(red, green, blue, builtin) led(red, green, blue, builtin);

struct LED {
    static const int init = 1;
    static const int no_fix = 2;
    static const int fix = 3;
    static const int no_fix_fallback = 4;
    static const int failure = 5;
};

#define LED_INIT            RGB(0,0,0,1);
#define LED_NO_FIX          RGB(0,0,1,0);
#define LED_FIX             RGB(0,1,0,0);
#define LED_NO_FIX_FAILBACK RGB(1,0,0,0);
#define LED_FAILURE         RGB(1,1,1,1);
#define LED_DISABLE         RGB(0,0,0,0);

#define MAX

#define LED_CYCLE_INTERVAL 1000

void ledCheck();
void ledSetup();
void setBlinksState(int blinks);

#endif /* SRC_LED_LED_H_ */
