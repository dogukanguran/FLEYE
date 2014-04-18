#include <Servo.h>
#include <Kalman.h>
#include <Motors.h>
#include <FlightControl.h>

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

const int frequency_print_offset = 4;
const int angle_print_offset =  frequency_print_offset+7;
const int motor_print_offset = angle_print_offset+17;
const int control_print_offset = motor_print_offset+7;


void setup(){
  Wire.begin();
  imu.init();
  motors.init();


  //End of the setup phase
  Serial.print("Setup done");
  calibrating = false;
}


void loop(){
  // Measure loop rate
  start_loop = micros();
  freq = 1000000/loop_time;

  //IMU
  if (! (imu.processAngles(angles, rates))  ) //continue only the data from the IMU is acceptable
  {
    IMU_problem = true;
    Serial.print( "    IMU PROBLEM   ");
  }
  
  //Motors
  motorsReady = !IMU_problem && !calibrating;
  if(!motorReady)
    motorOn = false;
  else
    motorOn = true;
  
  motors.setMotorsOn(motorsOn);
  motorsReadyOld = motorsReady;

  if(motorsReady)
    
}

