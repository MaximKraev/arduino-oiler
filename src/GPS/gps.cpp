#include "gps.h"
#include "GPSport.h"

NMEAGPS  gps;
gps_fix  fix_data;

NeoGPS::Location_t oldpos;
static bool firstInit = true;
static bool hasFix = false;

cCallbackFloat *_distanceCallback;
cCallbackBool *_fixCallback;

static void onFixChange(bool _hasFix) {
  _fixCallback->Execute(_hasFix);
  hasFix = _hasFix;
}

static void onGPSData(gps_fix fix) {
  if (fix.valid.location) {
    if (!hasFix) {
      onFixChange(true);
    }
    if (firstInit) {
      firstInit = false;
    }
    else {
      float range = fix.location.DistanceKm(oldpos);
      _distanceCallback->Execute(range*1*SEC);
    }
    oldpos = NeoGPS::Location_t(fix.latitudeL(), fix.longitudeL());
  }
  else {
    firstInit = true; // reset if we lost fix
    if (hasFix) {
      onFixChange(false);
    }
  }
}

void GPSCheck() {
  while (gps.available( gps_port )) {
    fix_data = gps.read();
    onGPSData(fix_data);
  }
}

void GPSSetup(TCallbackFloat *distanceCallback, TCallbackBool *fixCallback) {
  _distanceCallback = distanceCallback;
  _fixCallback = fixCallback;
  _fixCallback->Execute(false);
  DEBUG_PRINT( F("NMEA.INO: started\n") );
  gps_port.begin(9600);
}

