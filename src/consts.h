#ifndef CONSTS_H
#define CONSTS_H

#ifdef ARDUINO_ESP8266_NODEMCU
  #define NODEMCU
  #define OTA_SUPPORTED
#endif

#ifndef NODEMCU
  // inputs/outputs for other boards
  #define PUMP_BUTTON 4
  #define PUMP 2

  //#define RAIN_SENSOR 4

  #define LED_RED 5
  #define LED_GREEN 3
  #define LED_BLUE 6

  #define GPS_RX 8 // version 2
#endif

#ifdef NODEMCU // nodeMCU inputs
  #define PUMP_BUTTON D5
  #define PUMP D1

  #define LED_RED D2
  #define LED_GREEN D3
  #define LED_BLUE D4

  #define GPS_RX D6
#endif

#define SEC 1000
#define MIN SEC*60
#define HOUR MIN*60

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
#define DROP_RATE_MS 30L*1000 // every 40s second 65 km/h
#define MINIMUM_SPEED 15.0 // km/h
#define MAXIMUM_SPEED 200.0 // km/h
#define RANGE_MIN_DISTANCE MINIMUM_SPEED/60/60*1000 // m/s
#define RANGE_MAX_DISTANCE MAXIMUM_SPEED/60/60*1000 // m/s

#define PUMP_ACTIVATE_DISTANCE 65000/3600*DROP_RATE_MS/1000 // use DROP_RATE_MS/1000 on 65km/h
                               // m/s    * s

// test values
#ifdef TEST_VALUES
#define PUMP_ACTIVATE_DISTANCE 30
#define MINIMUM_SPEED 0.1
#define NO_FIX_TIMEOUT 10L*1000 // 0.5 minute
#define NO_FIX_START_TIMEOUT 30L*1000
#endif

#endif
