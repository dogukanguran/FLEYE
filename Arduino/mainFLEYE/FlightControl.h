#ifndef FlightControl_h
#define FlightControl_h

#include <Utils.h>
#include <math.h>
#include "Motors.h"
#include <Arduino.h>
#include "GPS.h"
#include "IMU.h"

//motor1: first white, motor2 second white
//4 and 2 counter clockwise

#define MAX_I_TERM 3
#define CONTROL_ON 1
//#define ANGLE_LOOP_DIVIDER 7 //the angle loop runs ANGLE_LOOP_DIVIDER times slower than the speed loop
//#define LOOP_TIME 2630

class FlightControl{
public:
  FlightControl();
  void control(float targetAngles[], float angles[], float rates[], float throttle, Motors &motors, bool motorsReady, IMU &imuInfo, GPS &gpsInfo);
  int getAngleLoopDivider();
  int getLoopTime();
  int getTargetInfo(GPS &gps, IMU &imu); // checks the target degree with the current degree and sends '1' to turn the quad left or sends '2' to turn the quad right and '0' not to change direction.
  //void getLoopTime(long l);

  //PID coefficients
  float kp_rate_roll;
  float kp_rate_pitch;
  float kp_rate_yaw;

  float kd_rate_roll;
  float ki_rate_roll;

  float kp_roll;
  float kp_pitch;
  float kp_yaw;

  float kd_roll;
  float kd_pitch;
  float kd_yaw;

  float ki_roll;
  float ki_pitch;
  float ki_yaw;

  long loop_time;
  char i_max;
  bool i_on;
  
  int leftOrRight ;
  IMU* imu;
  GPS* gps;
private:
  float U1, U2, U3, U4;  // coefficients of each motor
  float w1, w2, w3, w4;  // pwm values for each motor

  float targetRate[3];   

  // PID Tuning
  int incomingByte;
  float multiplier;

  int max_I_term;

  // Angles errors
  float anglesErrors[3];
  float anglesErrorsD[3];
  float anglesErrorsOld[3];
  float anglesErrorsSum[3];

  // Rates errors
  float ratesErrors[3];
  float ratesErrorsD[3];
  float ratesErrorsOld[3];
  float ratesErrorsSum[3];

  // sortie
  float sortiePIDangle[3];
  float sortiePIDrate[3];

  float angle_loop_time;
  int counter_angle_loop;
};

#endif

