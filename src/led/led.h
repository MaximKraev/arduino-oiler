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

enum LED {
    INIT,
    NO_FIX,
    FIX,
    NO_FIX_FALLBACK,
    FAILURE
};

#define LED_INIT            RGB(0,0,0,1);
#define LED_NO_FIX          RGB(0,0,1,0);
#define LED_FIX             RGB(0,1,0,0);
#define LED_NO_FIX_FAILBACK RGB(1,0,0,0);
#define LED_FAILURE         RGB(1,1,1,1);
#define LED_DISABLE         RGB(0,0,0,0);

#define MAX

#define LED_CYCLE_INTERVAL 500

void ledCheck();
void ledSetup();
void setBlinksState(LED status);

#endif /* SRC_LED_LED_H_ */
