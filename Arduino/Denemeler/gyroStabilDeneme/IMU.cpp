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
  altimeter.enableDefault();
  delay(100); // Wait for sensor to stabilize

  gyro.read();
  compass.read();

  //Set Starting angles
  accX = compass.m.x;
  accY = compass.m.y;
  accZ = compass.m.z;
  gyroX = gyro.g.x;
  gyroY = gyro.g.y;
  gyroZ = gyro.g.z;

  pressure = altimeter.readPressureMillibars();
  altitude = altimeter.pressureToAltitudeMeters(pressure);
  temperature = altimeter.readTemperatureC();

  landingValue = altitude / ALTIMETER_DIVIDER;
  currentValue = landingValue;
  targetValue = landingValue + 1;

  throttle = MIN_THROTTLE_VALUE;
  landing = false; // FLEYE is taking off from the ground
  flying = false; // FLEYE is not flying, FLEYE is taking off or landing.

  Serial.println("ACC Values:");
  Serial.print("AccX : ") ; 
  Serial.print(accX);
  Serial.print("AccY : ") ; 
  Serial.print(accY);
  Serial.print("AccZ : ") ; 
  Serial.println(accZ);
  Serial.println("GYRO Values:");
  Serial.print("GyroX : ") ; 
  Serial.print(gyroX);
  Serial.print("GyroY : ") ; 
  Serial.print(gyroY);
  Serial.print("GyroZ : ") ; 
  Serial.println(gyroZ);
  Serial.println("");

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

void IMU::updateAltimeterValue(){
  pressure = altimeter.readPressureMillibars();
  altitude = altimeter.pressureToAltitudeMeters(pressure);
  temperature = altimeter.readTemperatureC();
  Serial.print("Altitude : "); 
  Serial.println(altitude);
  landingValue = altitude / ALTIMETER_DIVIDER;
  currentValue = landingValue;
}

float IMU::getThrottle(){
  updateAltimeterValue();
  switch(isFlying()){
  case true:
    throttle = AVG_THROTTLE_VALUE;
    targetValue = currentValue - 1; 
    ; 
    break;
  case false:
    switch(isLanding()){
    case true:
      if(currentValue > targetValue){
        throttle -= THROTTLE_MULTIPLIER;
        if(throttle < MIN_THROTTLE_VALUE)
          throttle = MIN_THROTTLE_VALUE;
      }
      ; 
      break;
    case false:
      if(currentValue < targetValue){
        throttle += THROTTLE_MULTIPLIER;
        if(throttle > MAX_THROTTLE_VALUE)
          throttle = MAX_THROTTLE_VALUE;
      }
      else if (currentValue == targetValue){
        flying = true;
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
  gyro.read();
  compass.read();			
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

  //  Serial.print("compAngleX : "); Serial.println(compAngleX);
  //  Serial.print("compAngleY : "); Serial.println(compAngleY);  

  timer = micros(); 

  //45 deg rotation for roll and pitch (depending how your IMU is fixed to your quad)
  angles[0]=  -rac22* compAngleX + rac22*compAngleY + ROLL_OFFSET;
  angles[1]=  -rac22* compAngleX - rac22*compAngleY +2*rac22*PI*RAD_TO_DEG + PITCH_OFFSET;
  angles[2]=  gyroZangle;

  rates[0]=   -  rac22* gyroXrate + rac22*gyroYrate;
  rates[1]= - rac22* gyroXrate - rac22*gyroYrate;
  rates[2]=  gyroZrate;

  //  Serial.println("IMU.cpp");
  //  Serial.println("Angles : ");
  //  Serial.print(angles[0]);
  //  Serial.print(",");
  //  Serial.print(angles[1]);
  //  Serial.print(",");
  //  Serial.println(angles[2]);
  //  Serial.println("Rates : ");
  //  Serial.print(rates[0]);
  //  Serial.print(",");
  //  Serial.print(rates[1]);
  //  Serial.print(",");
  //  Serial.println(rates[2]);
  //  Serial.println("");
  //////* Print Data  for vib measurements*/
  //  switch (j)
  //  {
  //
  //  //	Frequency print
  //  case 1: 
  //  dtostrf(compAngleX - 180  ,6,2,StrAnglesvib);
  //  Serial.print(StrAnglesvib); 
  //  break;
  //  case 2:
  //  Serial.print("  ");
  //  break;
  //  case 3:
  //  dtostrf(gyroXangle -180,6,2,StrAnglesvib);	
  //  Serial.println(StrAnglesvib);
  //  j=0;
  //  break;
  //  }	   
  //  j++;

  if ( abs(angles[0]) < ROLL_MAX_IMU && abs(angles[1]) < PITCH_MAX_IMU  )
  {
    return true;
  }
  else
  {
    return false;
  }
}



