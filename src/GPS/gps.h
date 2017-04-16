#ifndef GPS_H
#define GPS_H
  #include <Arduino.h>
  #include <NMEAGPS.h>
  #include "debug.h"
  #include "consts.h"
  #include "callback/callback.h"

  #define RX_PIN 10
  #define TX_PIN 9

  #include <SoftwareSerial.h>
  #include "Streamers.h"

  void GPSSetup(TCallback &distanceReached);
  void GPSCheck();

#endif