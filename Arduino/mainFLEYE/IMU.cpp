#include "IMU.h"
#include <Wire.h>
#include <LSM303.h>
#include <L3G.h>
#include <math.h>
#include <stdint.h>
#include <LPS331.h>

IMU::IMU(){  

}

void IMU::init()
{
  // initialize device
  Wire.begin();
  gyro.init();
  compass.init();
  altimeter.init();
  gyro.enableDefault();
  compass.enableDefault();

  delay(100); // Wait for sensor to stabilize
  // read values from the sensors
  gyro.read();
  compass.read();
  
  //Set Starting angles
  accX = compass.m.x;
  accY = compass.m.y;
  accZ = compass.m.z;
  gyroX = gyro.g.x;
  gyroY = gyro.g.y;
  gyroZ = gyro.g.z;

  // setting the values of altimeter
  pressure = altimeter.readPressureMillibars();
  altitude = altimeter.pressureToAltitudeMeters(pressure); // altitude info is calculated with the air pressure.
  temperature = altimeter.readTemperatureC(); // current wheather tempeture.
  
  // calculating the values to keep track FLEYE's takeoff / landing situation. 
  landingValue = altitude / ALTIMETER_DIVIDER; // because the altimeter cannot give the exact value we need to filter and minimize the changes.
  currentValue = landingValue; // the current value that is real altitude / ALTIMETER_DIVIDER
  targetValue = landingValue + 1; // in the taking off condition, our target will be current + 1. this +1 means 25 meters

  // start with the minimum throttle value, this makes the motors start but not taking off.
  throttle = MIN_THROTTLE_VALUE;
  landing = false; // FLEYE is taking off from the ground
  flying = false; // FLEYE is not flying, FLEYE is taking off or landing.

  accXangle = (atan2(accX,accZ)+PI)*RAD_TO_DEG;
  accYangle = (atan2(accY,accZ)+PI)*RAD_TO_DEG; //400

  //kalmanX.setAngle(accXangle); // Set starting angle
  //kalmanY.setAngle(accYangle);
  //kalmanZ.setAngle(accZangle);

  gyroXangle = accXangle;
  gyroYangle = accYangle;
  gyroZangle = 0;

  alpha_gyro = 0.995; 
  c = (1-alpha_gyro)*1;     
  compAngleX = accXangle;   
  compAngleY = accYangle;
  compAngleX0 = accXangle;   

  //Gyro Calibration
  float n = 200;

  float sX = 0.0;
  float sY = 0.0;
  float sZ = 0.0;	

  for (int i = 0; i < n; i++)
  {
    gyroX = gyro.g.x;
    gyroY = gyro.g.y;
    gyroZ = gyro.g.z;
    sX += gyroX;
    sY += gyroY;
    sZ += gyroZ;
  }


  gyroXoffset = sX/n;
  gyroYoffset = sY/n;
  gyroZoffset = sZ/n;



  j=0;
}

// updates the altimeter value according to the current position and air pressure.
void IMU::updateAltimeterValue(){
  pressure = altimeter.readPressureMillibars();
  altitude = altimeter.pressureToAltitudeMeters(pressure);
  temperature = altimeter.readTemperatureC();
  //Serial.print("Altitude : "); 
  //Serial.println(altitude);
  // updates also landing value and current value.
  landingValue = altitude / ALTIMETER_DIVIDER;
  currentValue = landingValue;
}

// calculates the new throttle value depending on the our condition which is takingoff/landing or flying.
float IMU::getThrottle(){
  updateAltimeterValue();
  
  switch(isFlying()){
  // if FLEYE is flying then we need to stabilize it at the constant value.
  case true:
    throttle = AVG_THROTTLE_VALUE;
    targetValue = currentValue - 1; 
    ; 
    break;
  // if FLEYE is not flying then it must land or take off.  
  case false:
    switch(isLanding()){
    // if FLEYE is landing then the throttle value need to be decreased
    case true:
      if(currentValue > targetValue){
        throttle -= THROTTLE_MULTIPLIER;
        if(throttle < MIN_THROTTLE_VALUE)
          throttle = MIN_THROTTLE_VALUE;
      }
      ; 
      break;
    // if FLEYE is taking off then the throttle value need to be increased.  
    case false:
      if(currentValue < targetValue){
        throttle += THROTTLE_MULTIPLIER;
        if(throttle > MAX_THROTTLE_VALUE)
          throttle = MAX_THROTTLE_VALUE;
      }
      else if (currentValue == targetValue){
        flying = true; // if FLEYE reaches the target altitude, then it's condition need to be changed to flying.
      }
      ; 
      break;
    }; 
    break;
  }
  return throttle;
}

bool IMU::isFlying(){
  return flying;
}

bool IMU::isLanding(){
  return landing;
}

bool IMU::processAngles(float angles[],float rates[])
{
  // read values of the sensors(gyro and accelorameter)
  gyro.read();
  compass.read();
  // assigning values from the sensors			
  accX = compass.m.x;
  accY = compass.m.y;
  accZ = compass.m.z;
  gyroX = gyro.g.x;
  gyroY = gyro.g.y;
  gyroZ = gyro.g.z;

  //Filter
  accXf = filterX.update(accX);
  accYf = filterY.update(accY);
  accZf = filterZ.update(accZ);

  // ANGULAR RATES
  gyroXrate = (float) (gyroX-gyroXoffset)/131.0;  //140
  gyroYrate = -((float) (gyroY-gyroYoffset)/131.0);
  gyroZrate = ((float) (gyroZ-gyroZoffset)/131.0);

  //ACC ANGLES
  accYangle = (atan2(accXf,accZf)+PI)*RAD_TO_DEG;
  accXangle = (atan2(accYf,accZf)+PI)*RAD_TO_DEG; //400

  // GYRO ANGLES
  gyroXangle += gyroXrate*(float)(micros()-timer)/1000000;
  gyroYangle += gyroYrate*(float)(micros()-timer)/1000000;
  gyroZangle += gyroZrate*(float)(micros()-timer)/1000000;

  //Complementary filter  //200
  dt = (float)(micros()-timer)/1000000.0;
  compAngleX = alpha_gyro*(compAngleX+(gyroXrate*dt))   +   c*accXangle; // Calculate the angle using a Complimentary filter 
  compAngleY = alpha_gyro*(compAngleY+(gyroYrate*dt))  +   c*accYangle; // Calculate the angle using a Complimentary filter 
  //compAngleX0 = 0.997*(compAngleX0+(gyroXrate*(float)(micros()-timer)/1000000))   +   (1-0.997)*accXangle; // Calculate the angle using a Complimentary filter 

  timer = micros(); 

  //45 deg rotation for roll and pitch (depending how your IMU is fixed to your quad)
  angles[0]=  -rac22* compAngleX + rac22*compAngleY + ROLL_OFFSET;
  angles[1]=  -rac22* compAngleX - rac22*compAngleY +2*rac22*PI*RAD_TO_DEG + PITCH_OFFSET;
  angles[2]=  gyroZangle;

  rates[0]=   -  rac22* gyroXrate + rac22*gyroYrate;
  rates[1]= - rac22* gyroXrate - rac22*gyroYrate;
  rates[2]=  gyroZrate;

  //////* Print Data  for vib measurements*/
  //switch (j)
  //{

  ////	Frequency print
  //case 1: 
  //dtostrf(compAngleX - 180  ,6,2,StrAnglesvib);
  //Serial.print(StrAnglesvib); 
  //break;
  //case 2:
  //Serial.print("  ");
  //break;
  //case 3:
  //dtostrf(gyroXangle -180,6,2,StrAnglesvib);	
  //Serial.println(StrAnglesvib);
  //j=0;
  //break;
  //}	   
  //j++;

  if ( abs(angles[0]) < ROLL_MAX_IMU && abs(angles[1]) < PITCH_MAX_IMU  )
  {
    return true;
  }
  else
  {
    return false;
  }
}

