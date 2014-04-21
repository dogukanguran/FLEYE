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
  while(Serial.available() > 0 ){
    if(index < 19) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    }
    
    for(int i=0;i<20;i++)
    {
      Serial.print(inData[i] + " "); 
    }
  }
}

