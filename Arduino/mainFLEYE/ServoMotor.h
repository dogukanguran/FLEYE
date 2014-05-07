/*
  taken from github.
*/
#include <Servo.h>

#ifndef ServoMotor_h
#define ServoMotor_h

class ServoMotor{
private:
  Servo myServo;
  int minPos;
  int maxPos;
  boolean isHolding;
public:
  void init();
  void setMinMaxPosValues(int, int);
  void setIsHolding();
  void setEmpty();
  boolean isHolding();
  boolean letDrop();
  int getServoPin();
  int getMinPos();
  int getMaxPos();
}


#endif
