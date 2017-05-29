#ifndef CONSTS_H
#define CONSTS_H

// inputs/outputs

#define PUMP_BUTTON 4
#define PUMP 2

//#define RAIN_SENSOR 4

#define LED_RED 5
#define LED_GREEN 3
#define LED_BLUE 6

#define GPS_RX 8 // version 2
#define GPS_TX 9


// pump constants
#define PUMP_TICK_MS 100
#define PUMP_BUTTON_INTERVAL 450
#define PUMP_BUTTON_ACTIVE PUMP_TICK_MS // one drop per power

// failback
#define NO_FIX_TIMEOUT 30L*1000 // 30 sec minutes
#define NO_FIX_INTERVAL 20L*1000 // every 20 seconds
#define NO_FIX_START_TIMEOUT 5L*60*1000 // start timeout waiting for fix

//#define RAIN_FIX 0.6

// speed calculations
#define DROP_RATE_MS 18375 // every 18.375 second 40 miles per hour
#define MINIMUM_SPEED 15.0 // km/h
#define MAXIMUM_SPEED 200.0 // km/h
#define RANGE_MIN_DISTANCE MINIMUM_SPEED/60/60 // km/s
#define RANGE_MAX_DISTANCE MAXIMUM_SPEED/60/60 // km/s

#define PUMP_ACTIVATE_DISTANCE 64373.8/3600*DROP_RATE_MS/1000 // use DROP_RATE_MS on 64373.8 m/h

// test values
#ifdef TEST_VALUES
#define PUMP_ACTIVATE_DISTANCE .05
#define MINIMUM_SPEED 0.1
#define NO_FIX_TIMEOUT 10L*1000 // 0.5 minute
#endif

#endif
