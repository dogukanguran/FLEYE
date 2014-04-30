#ifndef IMU_h
#define IMU_h

#include <Wire.h>
#include <LSM303.h> // acc
#include <L3G.h> // gyro
#include <LPS331.h> // altimeter
#include "Arduino.h"
#include "Utils.h"
#include "Kalman.h"
#include "Filter.h"
#include <math.h>


//#define  ROLL_MAX_IMU  30
//#define  PITCH_MAX_IMU 30
//#define  ROLL_OFFSET -0.16
//#define  PITCH_OFFSET 2.10
//#define  YAW_OFFSET 0
//#define  MIN_THROTTLE_VALUE 0
//#define  AVG_THROTTLE_VALUE 200 // estimated value
//#define  MAX_THROTTLE_VALUE 750
//#define  THROTTLE_MULTIPLIER 30
//#define  ALTIMETER_DIVIDER 25

class IMU{
public:
  IMU();
  void init();  
  bool processAngles(float angles[],float rates[] );
  int getRollMaxImu();
  int getPitchMaxImu();
  float getRollOffset();
  float getPitchOffset();
  float getYawOffset();
  int getMinThrottleValue();
  int getAvgThrottleValue();
  int getMaxThrottleValue();
  int getThrottleMultiplier();
  int getAltimeterDivider();
  void updateAltimeterValue();
  float getThrottle();
  bool isLanding(); // indicates the FLEYE is taking off or landing.
  bool isFlying(); // indicates the FLEYE is not in the taking off / landing operations and goes to the target horizontally.
  
private:
  L3G gyro;
  LSM303 compass;
  LPS331 altimeter;
  
  int landingValue, // the value that the FLEYE is landing on the ground.
  currentValue, // current value which is divided by ALTIMETER_DIVIDER 
  targetValue;  // target value which is bigger one value from current value.
  float throttle; 
  bool landing, 
  flying;
  
  /* IMU Data */
  float accX, accY, accZ;
  float gyroX, gyroY, gyroZ;

  float accXangle, accYangle, accZangle; // Angle calculate using the accelerometer
  float gyroXangle, gyroYangle, gyroZangle; // Angle calculate using the gyro
  float kalAngleX, kalAngleY, kalAngleZ; // Calculate the angle using a Kalman filter
  float compAngleX, compAngleY, compAngleX0;

  uint32_t timer;
  float gyroXoffset, gyroYoffset, gyroZoffset;

  float gyroXrate ;
  float gyroYrate ;
  float gyroZrate;

  //float xv[NZEROS+1], yv[NPOLES+1];
  //float xv1[NZEROS+1], yv1[NPOLES+1];  
  float accXf;
  float accYf;
  float accZf;

  float pressure, altitude, temperature;

  Filter filterX;
  Filter filterY;	
  Filter filterZ;

  float alpha_gyro;
  float c;
  float dt;
  char StrAnglesvib[7];
  int j;
};

#endif

