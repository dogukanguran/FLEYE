#ifndef GPS_h
#define GPS_h

#include "TinyGPS.h"
#include <SoftwareSerial.h>

//#define METER_DIVIDER_GPS 100000 // if we divide the distance between 2 gps position  to METER_DIVIDER_GPS we are getting the meter value.

class GPS{
private:
  float curLat, curLon;
  float tarLat, tarLon;
  float midLat, midLon;
  unsigned long age;
  TinyGPS gps;

public:
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
  
  void init(){
    Serial.begin(4800);
    smartdelay(0);
  }

  int getGPSDivider(){
    return 100000;
  }

  void logout(){
    Serial.end();
  }

  // by the help of this line, we can track FLEYE's coordination.
  double findLineBetweenCurAndTar(){
    double line = sqrt((curLat - tarLat) * (curLat - tarLat) + (curLon - tarLon) * (curLon - tarLon));
    return line;
  }
  // Dividing the line in pieces make the FLEYE go the target almost on the line.
  double findMiddleCoordinationOf2Points(float tarLat, float tarLon){
    midLat = (curLat + tarLat) / 2 ;
    midLon = (curLon + tarLon) / 2 ;
  }

  void setTargetPosition(float lat,float lon){
    tarLat = lat; 
    tarLon = lon;
  }

  // gets positions.
  void getPosition(){
    init();
    gps.f_get_position(&curLat, &curLon, &age);
    logout();
  }

  float getLatitude(){
    getPosition();
    return curLat;
  }

  float getLongitude(){
    getPosition();
    return curLon;
  }

  unsigned long getAge(){
    getPosition();
    return age;
  }
};

#endif





