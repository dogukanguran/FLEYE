#include <SoftwareSerial.h>

void setup(){
  pinMode(7, INPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop(){
    //float no = Serial.parseFloat();
    //Serial.print(no);
    
    Serial.print(Serial.read());
    delay(1000); 
  }


