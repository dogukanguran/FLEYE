#include "ServoMotor.h"
// initializing the servo motor.
void ServoMotor::init(){
  myServo.attach(getServoPin()); // using the port 9 of the arduino uno
  setIsHolding(); // FLEYE initially holds the life jacket
  setMinMaxPosValues(0,90); // robotic servo motor will be open 90 degree.
}

int ServoMotor::getServoPin(){
  return 9; 
}

void ServoMotor::setMinMaxPosValues(int minPosition, int maxPosition){
  minPos = minPosition;
  maxPos = maxPosition;
}

void ServoMotor::setIsHolding(){
  holding = 1;
}

void ServoMotor::setEmpty(){
  holding = 0;
}

bool ServoMotor::isHolding(){
  return holding;
}

void ServoMotor::letDrop(){
  // opens the robotic hand 90 degree
  for(int i = getMinPos(); i <= getMaxPos(); i++){
    myServo.write(i);
    delay(15);
  }
  // close the hand after dropping.
  for(int i = getMaxPos(); i >= getMinPos(); i--){
    delay(15);
  }
  setEmpty(); // indicates FLEYE is not holding any life jacket.
}

int ServoMotor::getMinPos(){
  return minPos;
}

int ServoMotor::getMaxPos(){
  return maxPos;
}


