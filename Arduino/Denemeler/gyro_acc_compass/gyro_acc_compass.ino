#include <L3G.h>
#include <LSM303.h>
#include <Wire.h>
#include <string.h>

L3G gyro;
LSM303 compass;

void setup(){
  Serial.begin(9600);  
  Wire.begin();
  
  if(!gyro.init()){
    Serial.println("Failed to autodetect gyro type!");
    while(1);
  }
  
  gyro.enableDefault();
  
  compass.init();
  compass.enableDefault();
  /*
  Calibration values; the default values of +/-32767 for each axis
  lead to an assumed magnetometer bias of 0. Use the Calibrate example
  program to determine appropriate values for your particular unit.
  */
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}

void loop(){
  
  gyro.read();
//  String string = "";
//  string =  "Gyro ->";
//  string += "X:";
//  char *x,*y,*z;
//  sprintf(x,"%d",(int)gyro.g.x);
//  sprintf(y,"%d",(int)gyro.g.y);
//  sprintf(z,"%d",(int)gyro.g.z);
//  string += x;
//  string += "Y:";
//  string += y;
//  string += "Z:";
//  string += z;
  
  Serial.print("Gyro ->");
  Serial.print("X: ");
  Serial.print((int)gyro.g.x);
  Serial.print(" Y: ");
  Serial.print((int)gyro.g.y);
  Serial.print(" Z: ");
  Serial.print((int)gyro.g.z);
  
  compass.read();
  float heading = compass.heading();
//  char *head;
//  sprintf(head,"%d",heading);
//  string += "Compass:";
//  string += head;
  
  Serial.print(" Compass : ");
  Serial.print(heading);
  Serial.println(";");

//Serial.println(string);
  delay(1000);
}
