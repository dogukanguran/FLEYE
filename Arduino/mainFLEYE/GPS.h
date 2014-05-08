#ifndef GPS_h
#define GPS_h

#include "TinyGPS.h"
#include <SoftwareSerial.h>
#include <LSM303.h>

//#define METER_DIVIDER_GPS 100000 // if we divide the distance between 2 gps position  to METER_DIVIDER_GPS we are getting the meter value.

class GPS{
private:
  float firstLat, firstLon;
  float curLat, curLon;
  float tarLat, tarLon;
  float curDegree, tarDegree;
  unsigned long age;
  TinyGPS gps;
  LSM303 compass;
  
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
    getPosition();
    firstLat = curLat;
    firstLon = curLon;
  }

  int getGPSDivider(){
    return 100000;
  }
  
  void setTargetPosition(float newTargetLat, float newTargetLon){
    tarLat = newTargetLat;
    tarLon = newTargetLon;
  }
  
  void logout(){
    Serial.end();
  }

  // by the help of this line, we can track FLEYE's coordination.
  double findLineBetweenCurAndTar(){
    double line = sqrt((curLat - tarLat) * (curLat - tarLat) + (curLon - tarLon) * (curLon - tarLon));
    return line;
  }
  
  void setTargetReturn(){
    tarLat = firstLat;
    tarLon = firstLon;
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
  
  float findSlope(){
    return (curLon - tarLon) / (curLat - curLon);
  }
  
  float findTargetDegree(){
    tarDegree = atan(findSlope() * 180 / PI); 
    return tarDegree;
  }
  
  float getCurrentDegree(){
    curDegree = compass.heading();
    return curDegree;
  }
  
  
};

#endif





