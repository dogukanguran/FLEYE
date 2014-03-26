/*
Software Serial is being used to establish communication GPS Hardware
Ting GPS is a library that makes easy to reach gps info seperately.
*/
#include <TinyGPS.h>
#include <SoftwareSerial.h>
// Constants
#define rxPin 9      //rx pin in gps connection
#define txPin 8      //tx pin in gps connection
#define buttonPin 2  //the pin that the pushbutton is attached to

// set up the serial port
  TinyGPS gps;
  SoftwareSerial ss(9,8); // port that the gps is attached to
  //button state
  int buttonState = 0;
  boolean buttonPushed = false;
  // variables of gps info
  float flat, flon, fix_age;
  float falt, fmps, fkmph;
  String gpsInfoToSend;
  
void setup(){
  ss.begin(9600);
  Serial.begin(4800); // port that the xBee is attached to
  // the button that swimmer use to trigger
  pinMode(buttonPin, INPUT);
}

void loop(){
  while(!buttonPushed){
    buttonState = digitalRead(buttonPin);
    if(buttonState != 0){
      buttonPushed = true;
    }
  }
  //need to re-create in each iteration
  bool newData = false;
  if(buttonPus"hed == true){
    while(ss.available()){
      char c = ss.read();
      if(gps.encode(c))
        newData = true;
    }
    if(newData){
      // returns +/- latitude/longitude in degrees
      gps.f_get_position(&flat, &flon, &fix_age);
      falt = gps.f_altitude(); // +/- altitude in meters
      fmps = gps.f_speed_mps(); // speed in m/sec
      fkmph = gps.f_speed_kmph(); // speed in km/hr
      /*
      Message Syntax : LATITUDE;LONGITUDE;FIXAGE;ALTITUDE;SPEED(meter);SPEED(KM)
      */
      gpsInfoTosend = flat + ";" + flon + ";" + fix_age + ";" + falt + ";" + fmps + ";" + fkmph ;
      // Sending Information via xBee serial port
      Serial.print(gpsInfoToSend);
      // waiting 3 seconds to send new info
      delay(3000);
    }
  }
}

