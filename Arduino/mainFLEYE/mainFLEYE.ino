/*
  This is the main file of the arduino operates on the quad copter. 
  In that project I used the C and C++ together.
  
  PS: according to the (C++)standard that we follow during coding, all #define operations will be changed with the "get" methods, but some of them does not, because they are just extra info
 and making them a part of a class does not make sense. 
*/

#include <Arduino.h>
#include <Servo.h> // controls the engines ESC(electronic speed controller)
#include <Kalman.h> // filtering library for gyro values
#include "Motors.h" 
#include "FlightControl.h"
#include "IMU.h" // read and manipulates the gyro, acc, altimeter and compass data
#include <Wire.h> // need to add because extra hardware is being used.
#include <LSM303.h> // compass library
#include <LPS331.h> // altimeter
#include <L3G.h> // gyro
#include <math.h>
#include "GPS.h" 
#include <SoftwareSerial.h>
#include <TinyGPS.h> // library that reads the gps data from hardware

bool calibrating = true;
bool IMU_problem = false;
float max_X ;
float max_Y ;
float angles[3]; // angles will come from the imu.cpp
float rates[3]; // rates will come from the imu.cpp
float old_a;
float mdiff;

//Motors
Motors motors;
bool motorsReady = false;
bool motorsReadyOld = false;
bool motorsOn = false;

//IMU
IMU imu;

//FlightControl
FlightControl flightControl;
float targetAngles[3];
float throttle;

//GPS Location Info
GPS gps;
float flat, flon;
unsigned long age;

//Measuring time
unsigned long loop_time = 0;
unsigned long start_loop = 0;
int freq;
double deltaF;

//Printing
char StrMotor[4];
char StrMotorOn[4] = "ON";
char StrMotorOff[4] = "OFF";
char StrMotorReady[4] = "Rdy";
char StrControl[6];
char Strfreq[7];
char StrAngles[6];
char StrSpeed[4];	

int print_counter = 0;

const int frequency_print_offset = 4;
const int angle_print_offset =  frequency_print_offset+7;
const int motor_print_offset = angle_print_offset+17;
const int control_print_offset = motor_print_offset+7;

// setup function will be executed only 1 time.
void setup(){
  Wire.begin(); // need to begin to read data from hardware
  imu.init(); // need to initiliaze to read data from hardware
  motors.init(); // setting the motors info
  gps.init(); // need to initiliaze to read gps info from gps module

  //End of the setup phase
  Serial.print("Setup done");
  calibrating = false;
}


void loop(){
  // Measure loop rate
  start_loop = micros();
  freq = 1000000/loop_time;

  //IMU
  if (!(imu.processAngles(angles, rates))){ //continue only the data from the IMU is acceptable
    IMU_problem = true;
    Serial.print( "    IMU PROBLEM   ");
  }

  //Motors
  motorsReady = !IMU_problem && !calibrating;
  if(!motorsReady)
    motorsOn = false;
  else
    motorsOn = true;

  motors.setMotorsOn(motorsOn);
  motorsReadyOld = motorsReady;
  // these angles estimated values and can be changed after the area testing.
  targetAngles[0] = -50;
  targetAngles[1] = 50;
  targetAngles[2] = -30;

  // getting throttle multiplier according to the condition of the FLEYE at the moment.
  throttle = imu.getThrottle();
  // handle the stabilization issue.
  flightControl.control(targetAngles, angles, rates, throttle, motors, motorsReady, imu);
  
  /* GPS tracking code will be added. Currently gps tracking code is not completed. */
}




