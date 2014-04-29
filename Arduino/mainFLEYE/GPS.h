#ifndef GPS_h
#define GPS_h

#include "TinyGPS.h"
#include <SoftwareSerial.h>

class GPS{
private:
  float lat, lon;
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
  

  // gets positions.
  void getPosition(){
    init();
    gps.f_get_position(&lat, &lon, &age);
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




