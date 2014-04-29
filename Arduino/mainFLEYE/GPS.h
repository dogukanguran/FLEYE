#ifndef GPS_h
#define GPS_h

#include "TinyGPS.h"
#include <SoftwareSerial.h>

#define METER_DIVIDER_GPS 100000 // if we divide the distance between 2 gps position  to METER_DIVIDER_GPS we are getting the meter value.

class GPS{
private:
  float curLat, curLon;
  float tarLat, tarLon;
  float midLat, midLon;
  unsigned long age;
  TinyGPS gps;
  
public:

  void init(){
    Serial.begin(4800);
    smartdelay(0);
  }
  
  void logout(){
    Serial.end();
  }
  
  // makes the active delay without any intruption
  void smartdelay(unsigned long ms){
    unsigned long start = millis();
    do 
    {
      while (Serial.available())
        gps.encode(Serial.read());
    } 
    while (millis() - start < ms);
  }
  
  double findLineBetweenTwoPoints(tarLat, tarLon){
    double line = sqrt((curLat - tarLat) * (curLat - tarLat) + (curLon - tarLon) * (curLon - tarLon));
    return line;
  }

  double findMiddleCoordinationOf2Points(tarLat, tarLon){
    midLat = (curLat + tarLat) / 2 ;
    mitLon = (curLon + tarLon) / 2 ;
  }
  
  // gets positions.
  void getPosition(){
    init();
    gps.f_get_position(&curLat, &curLon, &age);
    logout();
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




