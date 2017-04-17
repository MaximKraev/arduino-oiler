#include "gps.h"
#include "GPSport.h"

NMEAGPS  gps;
gps_fix  fix_data;

NeoGPS::Location_t oldpos;
bool firstInit = true;
bool hasFix = false;

cCallback *_distanceCallback;
cCallback *_fixCallback;

void onFixChange(bool _hasFix) {
  _fixCallback->Execute((void *) _hasFix);
  hasFix = _hasFix;
}

void onGPSData(gps_fix fix) {
  if (fix.valid.location) {
    if (!hasFix) {
      onFixChange(false);
    }
    if (firstInit) {
      firstInit = false;
    }
    else {
      float range = fix.location.DistanceKm(oldpos);
      _distanceCallback->Execute((void*) &range);
    }
    oldpos = NeoGPS::Location_t(fix.latitudeL(), fix.longitudeL());
  }
  else {
    DEBUG_PRINT("No fix")
    firstInit = true; // reset if we lost fix
    if (hasFix) {
      onFixChange(false);
    }
  }
}

void GPSCheck()
{
  while (gps.available( gps_port )) {
    fix_data = gps.read();
    onGPSData(fix_data);
  }
}

void GPSSetup(TCallback &distanceCallback, TCallback &fixCallback)
{
  _distanceCallback = &distanceCallback;
  _fixCallback = &fixCallback;
  DEBUG_PRINT( F("NMEA.INO: started\n") );
  gps_port.begin( 9600 );
}

