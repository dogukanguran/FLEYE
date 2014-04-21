#include <SoftwareSerial.h>

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup(){
  Serial.begin(9600);
  Serial.write("Power on.");
}

void loop(){
  while(Serial.available() == 0);
  while(Serial.available() > 21 ){
    if(Serial.read() == 0x7E){
      for(int i=0; i < 19 ; i++) {
         byte discardByte = Serial.read();
      }
      
      if(index < 19) // One less than the size of the array
      {
        Serial.print(Serial.read());
        Serial.print(", ");
      }
      Serial.println();
  }
  }
}

