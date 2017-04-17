#ifndef GPS_H
#define GPS_H
  #include "include.h"
  #include <NMEAGPS.h>
  #include "callback/callback.h"

  #define RX_PIN 10
  #define TX_PIN 9

  #include <SoftwareSerial.h>
  #include "Streamers.h"

  void GPSSetup(TCallback &distanceCallback, TCallback &fixCallback);
  void GPSCheck();

#endif