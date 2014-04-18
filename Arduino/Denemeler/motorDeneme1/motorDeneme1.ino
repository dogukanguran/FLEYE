int m1 = 3, m2 = 5, m3 = 6, m4 = 9;

void setup() 
{ 
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 


void loop() 
{ 
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(m1, speed);
      analogWrite(m2, speed);
      analogWrite(m3, speed);
      analogWrite(m4, speed);
    }
  }
} 

