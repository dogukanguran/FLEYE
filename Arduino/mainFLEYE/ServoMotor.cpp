/*
  taken from github.
 */
#include "ServoMotor.h"

void ServoMotor::init(){
  myServo.attach(9);
  setIsHolding();
  setMinMaxPosValues(0,90);
}

int ServoMotor::getServoPin(){
  return 9; 
}

void ServoMotor::setMinMaxPosValues(int minPosition, int maxPosition){
  minPos = minPosition;
  maxPos = maxPosition;
}

void ServoMotor::setIsHolding(){
  isHolding = true;
}

void ServoMotor::setEmpty(){
  isHolding = false;
}

boolean ServoMotor::isHolding(){
  return isHolding;
}

boolean ServoMotor::letDrop(){
  for(int i = getMinPos(); i <= getMaxPos(); i++){
    myServo.write(i);
    delay(15);
  }
  for(int i = getMaxPos(); i >= getMinPos(); i--){
    delay(15);
  }
  setEmpty();
}

int ServoMotor::getMinPos(){
  return minPos;
}

int ServoMotor::getMaxPos(){
  return maxPos;
}


