#include "FlightControl.h"
#include "Utils.h"
#include <math.h>

FlightControl::FlightControl() {
  //the angle loop runs ANGLE_LOOP_DIVIDER times slower than the speed loop
  angle_loop_time = getLoopTime() * getAngleLoopDivider();
  counter_angle_loop = getAngleLoopDivider();	

  //Setting up of the gain
  float ku = 3.0/100;
  kp_roll = 0.5*ku;
  ki_roll = 0.001*1.2*ku*2/angle_loop_time*1000000;
  kd_roll = 1000*0.075*ku*0.5*angle_loop_time/1000000;

  kp_rate_roll = 0.2;

  // I-term init
  anglesErrorsSum[0]=0;
  i_on = false;
  i_max='0';

  //incomingByte = 0;
  multiplier = 1.1;	
}

int FlightControl::getLoopTime(){
  return 2630;
}

int FlightControl::getAngleLoopDivider(){
  return 7;
}

void FlightControl::control(float targetAngles[], float angles[], float rates[], float throttle, Motors &motors, bool motorsReady, IMU &imuInfo, GPS &gpsInfo) {

  gps = &gpsInfo;
  imu = &imuInfo;
  //Position Loop
  if (counter_angle_loop==getAngleLoopDivider()){
    for (int i = 0; i < 2 ; i++){
      anglesErrors[i] = targetAngles[i] - angles[i];
      anglesErrorsD[i] = kd_roll*( anglesErrors[i] - anglesErrorsOld[i]) ;
      anglesErrorsSum[i] += i_on*ki_roll*anglesErrors[i];
      anglesErrorsSum[i]= i_on*constrain_f( anglesErrorsSum[i], -MAX_I_TERM, MAX_I_TERM);
      anglesErrorsOld[i] = anglesErrors[i];
      sortiePIDangle[i] = kp_roll * anglesErrors[i] + anglesErrorsSum[i] + anglesErrorsD[i];	
    }
    counter_angle_loop=0;
  }
  //Speed Loop 
  for (int i = 0; i < 2 ; i++){
    targetRate[i] = sortiePIDangle[i];
    ratesErrors[i] = targetRate[i] - rates[i];
  }

  leftOrRight = getTargetInfo(gpsInfo, imuInfo);
  if(leftOrRight == 0)
    U4=CONTROL_ON*0; //No Yaw control for the moment
  else if(leftOrRight == 1)
    U4 = CONTROL_ON * 0,5; // need to be tested to declare exact value
  else if(leftOrRight == 2)
    U4 = CONTROL_ON * -0,5; // need to be tested to declare exact value

  U2 = 1*CONTROL_ON*(kp_rate_roll * ratesErrors[0]);
  U3 = 1*CONTROL_ON*(kp_rate_roll * ratesErrors[1]);
  U1 = throttle*0.10;

  //Roll is control by M2 and M4 via U2
  //Ptich is control by M1 and M3 via U3

  w2=  1* (U1 + U2 + U4); // raw value of motor2  
  w1 = 1* (U1 + U3 - U4); // raw value of motor1
  w4 = 1* (U1 - U2 + U4); // raw value of motor4
  w3 = 1* (U1 - U3 - U4); // raw value of motor3
  
  if(imuInfo.isFlying())
    w4 += 1,0; // the estimated value. the value is needed to be tested.
    
  // if values are less then 0(zero), ensure that the value of these variables should be at least 0(zero).
  if (w1<0){
    w1=0;
  } 
  
  if (w2<0) {
    w2=0;
  }

  if (w3<0) {
    w3=0;
  }

  if (w4<0) {
    w4=0;
  } 

  if (i_on)
  {
    i_max='1';
  }
  else
  {
    i_max='0';
  }

  // set motor speeds
  motors.setMotorSpeed(1, 1*w1);
  motors.setMotorSpeed(2, 1*w2);
  motors.setMotorSpeed(3, 1*w3);
  motors.setMotorSpeed(4, 1*w4);

  counter_angle_loop++;
}

int getTargetInfo(GPS &gps, IMU &imu){
  if(imu.isFlying()){
    float curDegree, tarDegree;
    float diff;

    curDegree = gps.getCurrentDegree();
    tarDegree = gps.findTargetDegree();

    diff = (tarDegree - curDegree) / 2.0;

    if(diff < -10.0)
      return 1; // makes quadcopter turn left
    else if( diff > 10.0)
      return 2; // makes quadcopter turn right
    else
      return 0;  // makes quadcopter not to change direction.
  }
  else 
    return 0;
}




