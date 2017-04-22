#ifndef GPS_H
#define GPS_H

#include "include.h"
#include <NMEAGPS.h>
#include "callback/callback.h"

#define RX_PIN GPS_RX
#define TX_PIN GPS_TX

#include <SoftwareSerial.h>
#include "Streamers.h"

void GPSSetup(TCallbackFloat *distanceCallback, TCallbackBool *fixCallback);
void GPSCheck();

#endif
