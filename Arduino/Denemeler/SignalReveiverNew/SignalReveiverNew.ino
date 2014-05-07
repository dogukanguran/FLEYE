#include <SoftwareSerial.h>

void setup(){
  Serial.begin(9600);
}

void loop(){
  while(Serial.available() > 0 ) {
    Serial.println(Serial.read());
  }
  delay(1000);

}

