#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <L3G.h>
#include <LPS331.h>
#include <LSM303.h>

#define RXPIN 2
#define TXPIN 3
#define GPSBAUD 4800

LSM303 compass;
LPS331 ps;
L3G gyro;
TinyGPS gps;
SoftwareSerial ss(RXPIN, TXPIN);

float flat, flon;

void setup(){
  Serial.begin(115200);
  ss.begin(GPSBAUD);
  Wire.begin();
  gyro.init();
  gyro.enableDefault(); 
  ps.init();
  ps.enableDefault();
  compass.init();
  compass.enableDefault();

  /*
  Calibration values; the default values of +/-32767 for each axis
   lead to an assumed magnetometer bias of 0. Use the Calibrate example
   program to determine appropriate values for your particular unit.
   */
  compass.m_min = (LSM303::vector<int16_t>){
    -32767, -32767, -32767  };
  compass.m_max = (LSM303::vector<int16_t>){
    +32767, +32767, +32767  };
}

void loop(){
  bool newData = false;

  ss.listen();
  while(ss.available()){
    char c = ss.read();
    if(gps.encode(c))
      newData = true;
  }

  if(newData){
    gps.f_get_position(&flat, &flon);
    Serial.print("Lat:");
    Serial.println(flat);
    Serial.print("Lon:");
    Serial.println(flon);
    Serial.println("--");
  }
  else{
    Serial.println("GPS Bilgisi Yok!");
    Serial.println("--");
  }

  gyro.read();

  Serial.print("GYRO: ");
  Serial.print("X: ");
  Serial.print((float)gyro.g.x);
  Serial.print(" Y: ");
  Serial.print((float)gyro.g.y);
  Serial.print(" Z: ");
  Serial.println((float)gyro.g.z);
  Serial.println("--");

  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();

  Serial.print("p: ");
  Serial.print(pressure);
  Serial.print(" mbar\ta: ");
  Serial.print(altitude);
  Serial.print(" m\tt: ");
  Serial.println(temperature);
  Serial.print("deg C");
  Serial.println("--");

  compass.read();
  float heading = compass.heading();
  Serial.print("Compass :");
  Serial.println(heading);
  Serial.println("--");

  delay(1000);
}



