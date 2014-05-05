#include <Servo.h>

Servo myServo;

int pos;

void setup(){
  myServo.attach(9);
}


void loop(){
  for(pos = 0; pos < 90; pos += 1){
    myServo.write(pos);
    delay(15);
  }
  for(pos = 90; pos >= 1; pos -= 1){
    myServo.write(pos);
    delay(15);
  }
}
