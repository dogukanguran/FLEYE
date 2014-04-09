#include <SoftwareSerial.h>

void setup(){
  Serial.begin(9600);
}

void loop(){
  while(Serial.available() == 0);
  while(Serial.available() > 0 ){
    char input = Serial.read();
    if(input != ' ')
      Serial.print(input);
  }
}

