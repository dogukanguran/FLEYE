int m0 = 5, m1 = 6, m2 = 10; 
int m3 = 11;


void motorZeroLevel(){
  analogWrite(m0,125);
 analogWrite(m1,125);
  analogWrite(m2,125);
  analogWrite(m3,125);
}

void motorInc(){
  analogWrite(m0,254);
  analogWrite(m1,254);
analogWrite(m2,254);
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
  pinMode(m0,OUTPUT); 
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
}

void loop(){
  if(Serial.available()){
    int value = Serial.parseInt();
    if(value == 2)
      motorInc();
    if(value == 1)
      motorZeroLevel();
    if(value == 0)
      motorStop();
  }
}








