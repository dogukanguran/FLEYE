#include<SoftwareSerial.h>
#include <Servo.h>

Servo myServo1, myServo2, myServo3, myServo4;


void setup(){
  Serial.begin(9600);
  myServo1.attach(3);
  myServo2.attach(5);
  myServo3.attach(6);
  myServo4.attach(9);
  myServo1.write(0);
  myServo2.write(0);
  myServo3.write(0);
  myServo4.write(0);
  delay(3000); 
}

void loop(){
  //  while(Serial.available() == 0);
  //  while(Serial.available() > 0 ){
  //    char input = Serial.read();
  //    if(input != ' ')
  //      Serial.print(input);
  //  }

  for (int speed = 0 ; speed < 180 ; speed++){                     
    myServo1.write(speed);
    myServo2.write(speed);
    myServo3.write(speed);
    myServo4.write(speed);       
    delay(15);                                                  
  }

  for (int speed = 180 ; speed > 0 ; speed--){                     
    myServo1.write(speed);
    myServo2.write(speed);
    myServo3.write(speed);
    myServo4.write(speed);       
    delay(15);                                                  
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






