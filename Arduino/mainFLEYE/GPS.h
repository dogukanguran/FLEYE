#ifndef GPS_h
#define GPS_h

#include "TinyGPS.h"
#include <SoftwareSerial.h>


#define GPSRX 3
#define GPSTX 2

SoftwareSerial ss(GPSRX, GPSTX);

class GPS{
private:
  float lat, lon;
  unsigned long age;
  TinyGPS gps;
  //SoftwareSerial ss(GPSRX, GPSTX);

public:

  void init(){
    ss.begin(4800);
    smartdelay(0);
  }
  

  void smartdelay(unsigned long ms){
    unsigned long start = millis();
    do 
    {
      while (ss.available())
        gps.encode(ss.read());
    } 
    while (millis() - start < ms);
  }
  

  // gets positions.
  void getPosition(){
    smartdelay(0);
    gps.f_get_position(&lat, &lon, &age);
  }
  

  float getLatitude(){
    getPosition();
    return lat;
  }
  

  float getLongitude(){
    getPosition();
    return lon;
  }
  

  unsigned long getAge(){
    getPosition();
    return age;
  }
};

#endif




