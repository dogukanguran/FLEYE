int m0 = 5, m1 = 6, m2 = 10; 
int m3 = 11;

int buttonState = 0;         // when button is finished buttonState will have a value of HIGH
bool isButtonPushed = false; 

void motorZeroLevel(){
  analogWrite(m0,125);
<<<<<<< HEAD
  analogWrite(m1,125);
=======
 analogWrite(m1,125);
>>>>>>> FETCH_HEAD
  analogWrite(m2,125);
  analogWrite(m3,125);
}

void motorInc(){
  analogWrite(m0,254);
  analogWrite(m1,254);
<<<<<<< HEAD
  analogWrite(m2,254);
=======
analogWrite(m2,254);
>>>>>>> FETCH_HEAD
  analogWrite(m3,254);
}

void motorStop(){
  analogWrite(m0,20);
  analogWrite(m1,20);
  analogWrite(m2,20);
  analogWrite(m3,20);
}

void setup(){
  Serial.begin(9600);
<<<<<<< HEAD
  
=======
>>>>>>> FETCH_HEAD
  pinMode(m0,OUTPUT); 
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
}

boolean flag = false;

void loop(){
  if(Serial.available()){
    if(flag == false){
    motorZeroLevel();
    delay(1000);
    motorInc();
    flag = true;  
  }
    delay(5000);
    if(flag == true)
      motorStop();
    
  }
}


//void getgps(TinyGPS &gps)
//{
//  float latitude, longitude;
//  gps.f_get_position(&latitude, &longitude);
//  // Serial.print("Lat/Long: "); 
//  Serial.print(latitude,5); 
////  Serial.print(", "); 
////  Serial.println(longitude,5);
////  
////  Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());  
////  Serial.print("Course (degrees): "); Serial.println(gps.f_course()); 
////  Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
////  Serial.println();
////  
//  // Here you can print statistics on the sentences.
//  unsigned long chars;
//  unsigned short sentences, failed_checksum;
//  gps.stats(&chars, &sentences, &failed_checksum);
//}







