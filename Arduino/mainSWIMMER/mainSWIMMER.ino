/*
  This is the main file of the arduino used by swimmer. 
 */

#include <TinyGPS.h>
#include <SoftwareSerial.h>

#define rxPin 2       //rx(receiver) pin for gps connection
#define txPin 3       //tx(transmitter) pin for gps connection
#define buttonPin 2   //the pin that the button is attacted

TinyGPS gps; // help us to parse the GPS sentence coming from the GPS module.
SoftwareSerial ss(rxPin, txPin); // defining the port that gps and arduino speaks

int buttonState = 0;         // when button is finished buttonState will have a value of HIGH
bool isButtonPushed = false; // flag for the button.
float latitude, longitude;   // keeps latitude and longitude info coming from GPS
String gpsInfoToSend;

void setup(){
  Serial.begin(115200); // will send the data via xBee
  ss.begin(4800);       // GPS uses the baudrate of 4800

    pinMode(buttonPin, INPUT);    // setting the port that the button is attached and arduino listens that port.
}

void loop(){
  // wait until the button is pu
  while(!isButtonPushed){
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      isButtonPushed = true;
    }
  }
  //need to re-create in each iteration
  bool newData = false;
  if(isButtonPushed == true){
    while(ss.available()){
      char c = ss.read();
      if(gps.encode(c))
        newData = true;
    }
    if(newData){
      // returns +/- latitude/longitude in degrees
      gps.f_get_position(&latitude, &longitude);
      // send the data via xBee
      Serial.print("Latitude"); 
      Serial.print(latitude);
      Serial.print("Longitude"); 
      Serial.print(longitude);
      // waiting 3 seconds to send new info
      delay(3000);
    }
  }
}


