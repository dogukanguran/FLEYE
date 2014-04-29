#include <SoftwareSerial.h>


void setup(){
  Serial.begin(9600);
  Serial.write("Power on.");
}

void loop(){
  while (Serial.available() > 0)
    {
       delay(5);
       Serial.print(Serial.read());
    }

}

