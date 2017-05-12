#ifndef CONSTS_H
#define CONSTS_H

#define PUMP_BUTTON 3
#define PUMP 2

//#define RAIN_SENSOR 4

#define LED_RED 5
#define LED_GREEN 6
#define LED_BLUE 10

#define PUMP_TICK_MS 50
#define PUMP_BUTTON_INTERVAL 450
#define PUMP_BUTTON_ACTIVE PUMP_TICK_MS // one drop per power

#define NO_FIX_TIMEOUT 2L*60*1000 // 2 minutes
#define NO_FIX_INTERVAL 200L*1000 // every 20 seconds

#define GPS_RX 8 // version 2
#define GPS_TX 9

//#define RAIN_FIX 0.6

// speed calculations
#define MINIMUM_SPEED 15.0 // km/h
#define MAXIMUM_SPEED 200.0 // km/h
#define RANGE_MIN_DISTANCE MINIMUM_SPEED/60/60 // km/s
#define RANGE_MAX_DISTANCE MAXIMUM_SPEED/60/60 // km/s

#define PUMP_ACTIVATE_DISTANCE 0.35 // every 1km

// test values
#ifdef TEST_VALUES
#define PUMP_ACTIVATE_DISTANCE .05
#define MINIMUM_SPEED 0.1
#define NO_FIX_TIMEOUT 0.5L*60*1000 // 0.5 minute
#endif

#endif
