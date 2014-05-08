#include <math.h>

double aX,aY;
double bX,bY;
double degree;
double slope;
int counter;

void setup(){
  Serial.begin(9600);
  Serial.println("Setup done");
  aX = 4;
  aY = 4;
  bX = 2;
  bY = 2;
  counter = 0;
}

void loop(){
  if(counter == 0){
    slope = (2.0 - 6) / (2.0 - 4);
    Serial.println(atan(slope));
    degree = atan(slope) * 180 / PI;
    Serial.print("Slope : ");
    Serial.println(slope,5);
    Serial.print("Degree : ");
    Serial.println(degree,5);
    slope = ( 6.0 - 2) / (2.0 - 4);
    Serial.println(atan(slope));
    degree = atan(slope) * 180 / PI;
    Serial.print("Slope : ");
    Serial.println(slope,5);
    Serial.print("Degree : ");
    Serial.println(degree,5);
    slope = ( -3.0+1) / (2+3.0);
    Serial.println(atan(slope));
    degree = atan(slope) * 180 / PI;
    Serial.print("Slope : ");
    Serial.println(slope,5);
    Serial.print("Degree : ");
    Serial.println(degree,5);
    counter++;
  }
}

