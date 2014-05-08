#ifndef ServoMotor_h
#define ServoMotor_h


#include <Servo.h>

class ServoMotor{
private:
  Servo myServo;
  int minPos;
  int maxPos;
  bool holding;
public:
  void init();
  void setMinMaxPosValues(int, int);
  void setIsHolding();
  void setEmpty();
  bool isHolding();
  void letDrop();
  int getServoPin();
  int getMinPos();
  int getMaxPos();
};


#endif
