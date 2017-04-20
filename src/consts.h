#ifndef CONSTS_H
#define CONSTS_H

#define PUMP_BUTTON 3
#define PUMP 2

#define RAIN_SENSOR 4

#define PUMP_TICK_MS 40
#define PUMP_BUTTON_INTERVAL 500
#define PUMP_BUTTON_ACTIVE 50

#define GPS_RX 6
#define GPS_TX 5

#define STATUS_LED LED_BUILTIN

#define RAIN_FIX 0.6

// speed calculations
#define MINIMUM_SPEED 15.0 // km/h
#define MAXIMUM_SPEED 200.0 // km/h
#define RANGE_MIN_DISTANCE MINIMUM_SPEED/60/60 // km/s
#define RANGE_MAX_DISTANCE MAXIMUM_SPEED/60/60 // km/s

#define PUMP_ACTIVATE_DISTANCE 1.0 // every 1km

// test values
#ifdef TEST_VALUES
#define PUMP_ACTIVATE_DISTANCE .05
#define MINIMUM_SPEED 0.1
#endif

#endif
