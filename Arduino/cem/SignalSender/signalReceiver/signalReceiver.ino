#include<SoftwareSerial.h>

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
  
//  while(Serial.available() == 0);
//  while(Serial.available() > 0){
//    inByte = Serial.read();
//    while(inByte != '\n'){
//      inString += inByte;
//    }
//    Serial.println(inString);
//  }

}


