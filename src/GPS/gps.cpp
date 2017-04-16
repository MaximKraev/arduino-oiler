#include "gps.h"
#include "GPSport.h"

NMEAGPS  gps;
gps_fix  fix_data;

NeoGPS::Location_t oldpos;
bool firstInit = true;

cCallback *_distanceCallback;

void onGPSData(gps_fix fix) {
  if (fix.valid.location) {
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
  }
}

void GPSCheck()
{
  while (gps.available( gps_port )) {
    fix_data = gps.read();
    onGPSData(fix_data);
  }
}

void GPSSetup(TCallback &distanceCallback)
{
  _distanceCallback = &distanceCallback;
  DEBUG_PORT.print( F("NMEA.INO: started\n") );
  gps_port.begin( 9600 );
}

