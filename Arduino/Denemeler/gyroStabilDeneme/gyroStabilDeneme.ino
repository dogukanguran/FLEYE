#include <Arduino.h>
#include <Servo.h>
#include <Kalman.h>
#include "FlightControl.h"
#include "IMU.h"
#include <Wire.h>
#include <LSM303.h>
#include <LPS331.h>
#include <L3G.h>
#include <math.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "Motors.h"

bool calibrating = true;
bool IMU_problem = false;
float max_X ;
float max_Y ;
float angles[3];
float rates[3];
float old_a;
float mdiff;

//Motors
Motors motors;
bool motorsReady = false;
bool motorsReadyOld = false;
bool motorsOn = false;

//IMU
IMU imu;

//Servo
Servo myServo;

//FlightControl
FlightControl flightControl;
float targetAngles[3];
float throttle;

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
unsigned long start ;
const int frequency_print_offset = 4;
const int angle_print_offset =  frequency_print_offset+7;
const int motor_print_offset = angle_print_offset+17;
const int control_print_offset = motor_print_offset+7;

boolean deneme = false;
boolean yeter = true;
boolean indir;
int now;
boolean flag = true;
boolean flagHand = true;
void setup(){
  Serial.begin(9600);
  Wire.begin();
  imu.init();
  motors.init();
  throttle = 10;
  indir = false;
  myServo.attach(9);
  delay(5000);
  start = millis();
  //End of the setup phase
  Serial.println("Setup done");
  calibrating = false;
}


void loop(){
  if(Serial.available())
    deneme = true;
  if(deneme == true){
    if(flag == true){  
      // Measure loop rate
      start_loop = micros();
      freq = 1000000/loop_time;

      //IMU
//      if (!(imu.processAngles(angles, rates))){ //continue only the data from the IMU is acceptable
//        IMU_problem = true;
//        Serial.println( "    IMU PROBLEM   ");
//      }

      motorsReady = !IMU_problem && !calibrating; 
      motorsOn = true;
      motors.setMotorsOn(motorsOn);

      //targetAngles[0] = RadioChannels[4]*0.03-15;
      targetAngles[0] = -50;
      //targetAngles[1] = RadioChannels[2]*0.03-15;
      targetAngles[1] = 50;
      //targetAngles[2] = RadioChannels[3]*0.36-180;
      targetAngles[2] = -30;

      //throttle = imu.getThrottle();

      //  if((millis() - now) % 5000 == 0){
      //    if(deneme == true){
      //      throttle = throttle + 10;
      //      Serial.print("t1 : "); 
      //      Serial.println(throttle);
      //    }
      //    if(throttle == 50){
      //      deneme = false;
      //      indir = true;
      //    }  
      //    if(indir == true)
      //      throttle -= 10;
      //    if(throttle < 0)
      //      throttle = 0;  
      //  

      throttle = 10;
      imu.processAngles(angles, rates);
      flightControl.control(targetAngles, angles, rates, throttle, motors, motorsReady);

    }
    if(millis() - start > 10000)
      flag = false;

    if(flag == false){
      motors.allStop();
//      if(flagHand == true){
//        for(int i = 0; i <= 180; i++){
//          myServo.write(i);
//          delay(15);
//        }
//        delay(2000);
//        // close the hand after dropping.
//        for(int i = 180; i >= 0; i--){
//          delay(15);
//        }
//        flagHand = false;
//      }
    }
  }
}














