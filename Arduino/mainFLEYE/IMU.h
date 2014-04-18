#ifndef IMU_h
#define IMU_h

#include <Wire.h>
#include <LSM303.h>
#include <L3G.h>
#include "Arduino.h"
#include "Utils.h"
#include "Kalman.h"
#include "Filter.h"
#include <math.h>

#define  ROLL_MAX_IMU  30
#define  PITCH_MAX_IMU 30

#define  ROLL_OFFSET -0.16
#define  PITCH_OFFSET 2.10
#define  YAW_OFFSET 0

class IMU
{

public:

  IMU();
  void init();  
  bool processAngles(float angles[],float rates[] );

private:

  L3G gyro;
  LSM303 compass;

  /* IMU Data */
  int16_t accX, accY, accZ;
  int16_t gyroX, gyroY, gyroZ;

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

