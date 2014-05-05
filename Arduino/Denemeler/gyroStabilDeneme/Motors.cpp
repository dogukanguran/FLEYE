#include "Motors.h"

Motors::Motors(){  

  motors[0] = MOTOR_1_PIN;
  motors[1] = MOTOR_2_PIN;
  motors[2] = MOTOR_3_PIN;
  motors[3] = MOTOR_4_PIN;
  motorsOn = false;
}

void Motors::init(){
  
	pinMode(MOTOR_1_PIN, OUTPUT); 
	pinMode(MOTOR_2_PIN, OUTPUT); 
	pinMode(MOTOR_3_PIN, OUTPUT); 
	pinMode(MOTOR_4_PIN, OUTPUT); 
        setAllSpeed(0);
}

void Motors::allStop(){
  analogWrite(5,20);
  analogWrite(6,20);
  analogWrite(10,20);
  analogWrite(11,20);
}

void Motors::setMotorsOn(bool b){
	motorsOn = b;
}

void Motors::setMotorSpeed(byte motor, float speed){

	
	speed = map_f(speed, MIN_MOTOR_SPEED_CONTROL, MAX_MOTOR_SPEED_CONTROL, MIN_MOTOR_SPEED_PWM, MAX_MOTOR_SPEED_PWM);
//	speed = (speed *2) +MIN_MOTOR_SPEED_PWM - 6;
        
	//If the speed command is too high we just shut down all the motors
	//It might not be the best solution but it's at least safer for testing
	if (speed > 260)
	{
		allStop();
		Serial.print( " Motor command MAX ALL MOTORS STOPPED");
		while(1);
	}
		
	analogWrite(motors[motor-1], speed*motorsOn);
	motor_speeds[motor-1] = speed;
}


int Motors::getMotorSpeed(byte motor){
    return motor_speeds[motor-1];
}

void Motors::setAllSpeed(float speed){
     for (byte motor = 1; motor <= MOTOR_COUNT; motor++){
		setMotorSpeed(motor, speed);
    }
}





