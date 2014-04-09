/* Selam Cemcim,
 
 Bu program düzenli olarak her saniye xBee üzerinden "w"
 harfini gönderiyor. 
 
 xBee'ler default olarak 9600 baud üzerinden konuşuyorlar.
 eğer xBee'ni konfigür edeceksen 9600 baud üzerinden dinlediğini ve veri gönderdiğine emin ol, lütfen.
 Senin pc üzerinde xBee modülünü test etmen için yeterli olacaktır.
 */

#include <SoftwareSerial.h>
#include <TinyGPS.h>

//TinyGPS gps;
//SoftwareSerial ss(8,7);

//long lat, lon;
//unsigned long fix_age;

void setup(){
  Serial.begin(9600);
//  ss.begin(4800);
}

void loop(){
//  while(ss.available()){
//    if(gps.encode(ss.read())){
//      gps.get_position(&lat, &lon, &fix_age);
//      Serial.println(lat+";"+lon);
//      delay(1000);
//    }
//  }
 
 Serial.println("dogukan");
 delay(1000); 
  
}

