/* Selam Cemcim,
 
 Bu program düzenli olarak her saniye xBee üzerinden "w"
 harfini gönderiyor. 
 
 xBee'ler default olarak 9600 baud üzerinden konuşuyorlar.
 eğer xBee'ni konfigür edeceksen 9600 baud üzerinden dinlediğini ve veri gönderdiğine emin ol, lütfen.
 Senin pc üzerinde xBee modülünü test etmen için yeterli olacaktır.
 */

#include <SoftwareSerial.h>

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println("w");
  delay(1000);
}

