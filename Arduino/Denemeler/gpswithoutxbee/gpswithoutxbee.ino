#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define RXPIN 2
#define TXPIN 3
//Set this value equal to the baud rate of your GPS
#define GPSBAUD 4800

#define BUTTONPIN 7   // the number of the pushbutton pin
int buttonState = 0;
boolean isButtonPressed = false;




TinyGPS gps;
SoftwareSerial uart_gps(RXPIN, TXPIN);

void getgps(TinyGPS &gps);

void setup()
{
  Serial.begin(115200);
  uart_gps.begin(GPSBAUD);
  pinMode(BUTTONPIN, INPUT);
//  Serial.println("");
//  Serial.println("GPS Shield QuickStart Example Sketch v12");
//  Serial.println("       ...waiting for lock...           ");
//  Serial.println("");
}

void loop()
{
  while(!isButtonPressed){
    buttonState = digitalRead(BUTTONPIN);
    if (buttonState == HIGH) {     
      isButtonPressed = true;
    } 
  }
  while(uart_gps.available())     // While there is data on the RX pin...
  {
    int c = uart_gps.read();    // load the data into a variable...
    if(gps.encode(c))      // if there is a new valid sentence...
    {
      getgps(gps);         // then grab the data.
    }
  }
}

void getgps(TinyGPS &gps)
{
  float latitude, longitude, alti;
  gps.f_get_position(&latitude, &longitude);
//    Serial.print("Lat/Long: "); 
//    Serial.print(latitude,10); 
//    Serial.print(", "); 
//    Serial.println(longitude,10);
 
    //Serial.print("Altitude (meters): "); 
  alti = gps.f_altitude();  
//  Serial.println(alti);
//  Serial.print("Altitude ready (meters): "); Serial.println(gps.f_altitude());
  
  //  Serial.print("Course (degrees): "); 
  //  Serial.println(gps.f_course()); 
  //  Serial.print("Speed(kmph): "); 
  //  Serial.println(gps.f_speed_kmph());
  //  Serial.println();
  //
  //  // Here you can print statistics on the sentences.

  char buffer[50];
  sprintf(buffer, "%f;%f;%f", latitude, longitude, alti);
//  Serial.print("GPS Message : ");
  Serial.println(buffer);

  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
}


