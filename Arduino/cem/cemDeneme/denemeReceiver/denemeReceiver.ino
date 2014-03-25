#include<SoftwareSerial.h>

void setup(){
Serial.begin(9600);
}

void loop(){
  while(Serial.available() == false){
    Serial.print("waiting\n");
    Serial.print(Serial.read()+"\n");
  }
}
