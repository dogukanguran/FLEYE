void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println("asd");
  while(Serial.available())
    Serial.println(Serial.read());
  delay(1000);  
}
