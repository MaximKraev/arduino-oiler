#ifndef CONSTS_H
#define CONSTS_H

#ifdef ARDUINO_ESP8266_NODEMCU
  #define NODEMCU
//  #define OTA_SUPPORTED
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
  #define PUMP_BUTTON D8
  #define PUMP D1

  #define LED_RED D2
  #define LED_GREEN D3
  #define LED_BLUE D4

  #define GPS_RX D6
#endif

#define SECOND 1000L
#define MINUTE SECOND*60
#define HOUR MINUTE*60

// pump constants
#define PUMP_TICK_MS SECOND/10
#define PUMP_BUTTON_INTERVAL SECOND/2
#define PUMP_BUTTON_ACTIVE PUMP_TICK_MS // one drop per power

// failback
#define NO_FIX_TIMEOUT SECOND*30 // 30 sec minutes if we lost fix
#define NO_FIX_INTERVAL SECOND*60 // every 30 seconds
#define NO_FIX_START_TIMEOUT MINUTE*5 // start timeout waiting for fix

//#define RAIN_FIX 0.6

// speed calculations
#define DROP_RATE_MS SECOND*50 // every 30s if we do not have a fix
#define MINIMUM_SPEED 15.0 // km/h
#define MAXIMUM_SPEED 300.0 // km/h
#define RANGE_MIN_DISTANCE MINIMUM_SPEED/3600*1000 // m/s
#define RANGE_MAX_DISTANCE MAXIMUM_SPEED/3600*1000 // m/s

#define PUMP_ACTIVATE_DISTANCE 1500L // every 900 meters

//ota
#define WIFI_OTA_WAIT MINUTE*5

// test values
#ifdef TEST_VALUES
#define PUMP_ACTIVATE_DISTANCE 10
#define MINIMUM_SPEED 0.1
#define NO_FIX_TIMEOUT SECOND*10 // 0.5 minute
#define NO_FIX_START_TIMEOUT SECOND*30
#endif

#endif
