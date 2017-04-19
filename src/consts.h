#ifndef CONSTS_H
#define CONSTS_H

#define PUMP_BUTTON 5
#define PUMP 2

#define PUMP_INTERVAL 90000
#define PUMP_TICK_MS 40

#define RAIN_FIX 0.6

// speed calculations
#define MINIMUM_SPEED 15.0 // km/h
#define MAXIMUM_SPEED 250.0 // km/h
#define RANGE_MIN_DISTANCE MINIMUM_SPEED/60/60 // km/s
#define RANGE_MAX_DISTANCE MAXIMUM_SPEED/60/60 // km/s

#define PUMP_ACTIVATE_DISTANCE 1.0 // every 1km

// test values
#ifdef TEST_VALUES
#define PUMP_ACTIVATE_DISTANCE .05 // every 1km
#define MINIMUM_SPEED 0.1 // km/h
#endif

#endif
