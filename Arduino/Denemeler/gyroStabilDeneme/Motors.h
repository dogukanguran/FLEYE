#ifndef Motors_h
#define Motors_h

#include <Arduino.h>
#include "Utils.h"

#define MOTOR_COUNT 4

#define MOTOR_1_PIN 5
#define MOTOR_2_PIN 6
#define MOTOR_3_PIN 10
#define MOTOR_4_PIN 11

#define MIN_MOTOR_SPEED_PWM 75
#define MAX_MOTOR_SPEED_PWM 250

#define MIN_MOTOR_SPEED_CONTROL 0
#define MAX_MOTOR_SPEED_CONTROL 100


//1 and 3 clockwise (R on my props)
//4 and 2 counter clockwise


class Motors
{
  public:

    Motors();
    void init();
    void allStop();
    void setMotorSpeed(byte, float);
    int getMotorSpeed(byte);
    void setAllSpeed(float);
    void setMotorsOn(bool);
 
     
  private:
    int motors[MOTOR_COUNT];
    float motor_speeds[MOTOR_COUNT];
    bool motorsOn;
 };

#endif
