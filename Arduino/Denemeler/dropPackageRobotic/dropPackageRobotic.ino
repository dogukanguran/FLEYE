#include <TinyGPS.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define RXPIN 2
#define TXPIN 3
#define GPSBAUD 4800

TinyGPS gps;
Servo myServo;
int pos = 0;
SoftwareSerial uart_gps(RXPIN, TXPIN);

void getgps(TinyGPS &gps){
  float latitude, longitude, alti;
  gps.f_get_position(&latitude, &longitude);
  alti = gps.f_altitude();

  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
}

void setup(){
  Serial.begin(9600);
  uart_gps.begin(GPSBAUD);
  myServo.attach(9);
}

void loop(){
  while(!Serial.available());
  if(Serial.available() > 0){
    int value = Serial.parseInt();
    if(value == 1){
    Serial.print("111");
    for(pos = 0; pos < 90; pos++){
      myServo.write(pos);
      delay(15);
    }
    }
    else if(value == 2){
      Serial.print("222");
      for(pos = 90; pos > 0; pos--){
        myServo.write(pos);
        delay(15);
      }
    }
  }
}




