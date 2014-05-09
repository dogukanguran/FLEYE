#include <Servo.h>

Servo myServo;
bool flag;

void setup(){
myServo.attach(9);
flag = true;
delay(5000);
}

void loop(){
  if(flag == true){
  for(int i = 0; i <= 180; i++){
    myServo.write(i);
    delay(15);
  }
  // close the hand after dropping.
  for(int i = 180; i >= 0; i--){
    delay(15);
  }
  flag = false;
}}

