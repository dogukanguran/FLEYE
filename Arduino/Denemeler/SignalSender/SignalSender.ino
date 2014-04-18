#include <SoftwareSerial.h>


void setup(){
  Serial.begin(9600);
  delay(100);
}

void loop(){
  Serial.println("DogukanGuran");
  delay(1000); 

}


