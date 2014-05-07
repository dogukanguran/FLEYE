int buttonPin = 7;

boolean buttonState;
boolean isButtonPushed = false;
int counter = 0;
void setup(){
  Serial.begin(9600);
  pinMode(7, INPUT);  
}
void loop(){
buttonState = digitalRead(buttonPin);
if(buttonState == HIGH){
  isButtonPushed = true;
}

if(isButtonPushed == true){
  Serial.print("asdf");
  isButtonPushed = false;
}
}
