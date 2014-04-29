#include "FlightControl.h"
#include "Utils.h"
#include <math.h>

FlightControl::FlightControl() {

        //the angle loop runs ANGLE_LOOP_DIVIDER times slower than the speed loop
	angle_loop_time = LOOP_TIME* ANGLE_LOOP_DIVIDER;
	counter_angle_loop=ANGLE_LOOP_DIVIDER;	
  
	//Setting up of the gain
	float ku = 3.0/100;
	kp_roll = 0.5*ku;
	ki_roll = 0.001*1.2*ku*2/angle_loop_time*1000000;
	kd_roll = 1000*0.075*ku*0.5*angle_loop_time/1000000;

	kp_rate_roll = 0.2;
	
	// I-term init
	anglesErrorsSum[0]=0;
	i_on = false;
	i_max='0';
	
	incomingByte = 0;
	multiplier = 1.1;	

	
}

void FlightControl::control(float targetAngles[], float angles[], float rates[], float throttle, Motors &motors, bool motorsReady) {
  Serial.println("Roll values: ");	
  Serial.print("KP_roll : "); Serial.println(kp_roll);
                Serial.print("Kd_roll : "); Serial.println(kd_roll);
                Serial.print("Ki_roll : "); Serial.println(ki_roll);	
	//Setting gain of the PID
//	if (Serial.available() > 0) 
//	{ 
//		incomingByte = Serial.read();
//
//		if (incomingByte == 'P' )
//		{
//			Serial.print("Nouvelle valeur de kp_roll ");
//			kp_roll *= multiplier;
//			kd_roll *= multiplier;
//			ki_roll *= multiplier;
//			
//			//kp_rate_roll *= multiplier;
//			////ki_rate_roll *= multiplier;	
//			////kd_rate_roll *= multiplier;		
//		}
//		if (incomingByte == 'p' )
//		{
//			Serial.print("Nouvelle valeur de kp_roll ");
//			kp_roll /= multiplier;
//			kd_roll /= multiplier;
//			ki_roll /= multiplier;
//			
//			//kp_rate_roll /= multiplier;
//			//ki_rate_roll /= multiplier;
//			//kd_rate_roll /= multiplier;
//		}
//		
//		if (incomingByte == 'i' )
//		{
//			i_on=!i_on;
//		}
//		if (incomingByte == 'D' )
//		{
//			kd_roll *= multiplier;
//		}
//		if (incomingByte == 'd' )
//		{
//			kd_roll /= multiplier;
//		}
//		
//		if (incomingByte == 'R' )
//		{
//			kp_rate_roll *= multiplier;
//		}
//		if (incomingByte == 'r' )
//		{
//			kp_rate_roll /= multiplier;
//		}
//	}
	

	if (RATE_MODE)
	{
                Serial.println("RATE MODE");
		//Speed Loop
		//Only a Proportionnal feedback
		for (int i = 0; i < 2 ; i++)
		{
			//targetRate[i] = targetAngles[i];
			//ratesErrors[i] = targetRate[i] - rates[i];
			ratesErrors[i] = targetAngles[i] - rates[i];
			//ratesErrorsD[i] = kd_rate_roll*( ratesErrors[i] - ratesErrorsOld[i]) ;	
			//ratesErrorsSum[i] += i_on*ki_rate_roll*ratesErrors[i];
			//ratesErrorsSum[i]= i_on*constrain_f( anglesErrorsSum[i], -MAX_I_TERM, MAX_I_TERM);
			//ratesErrorsOld[i] = ratesErrors[i];
			sortiePIDrate[i] = kp_rate_roll * ratesErrors[i] ;//+  ratesErrorsSum[i] + ratesErrorsD[i];
		}
		U2 = 1*CONTROL_ON*kp_rate_roll * ratesErrors[0] ;
		U3 = 1*CONTROL_ON*kp_rate_roll * ratesErrors[1] ;
	}
	else
	{      
                Serial.println("RATE MODE ELSE");
                Serial.print("Counter angle loop : "); Serial.println(counter_angle_loop);
                Serial.print("Angle Loop Divider : "); Serial.println(ANGLE_LOOP_DIVIDER);
                
                
                
                //Position Loop
		if (counter_angle_loop==ANGLE_LOOP_DIVIDER)
		{
			for (int i = 0; i < 2 ; i++)
			{
				anglesErrors[i] = targetAngles[i] - angles[i];
				anglesErrorsD[i] = kd_roll*( anglesErrors[i] - anglesErrorsOld[i]) ;
				anglesErrorsSum[i] += i_on*ki_roll*anglesErrors[i];
				anglesErrorsSum[i]= i_on*constrain_f( anglesErrorsSum[i], -MAX_I_TERM, MAX_I_TERM);
				anglesErrorsOld[i] = anglesErrors[i];
				sortiePIDangle[i] = kp_roll * anglesErrors[i] + anglesErrorsSum[i] + anglesErrorsD[i];	
			}
			counter_angle_loop=0;
		}
		//Speed Loop 
		for (int i = 0; i < 2 ; i++)
		{
			targetRate[i] = sortiePIDangle[i];
			ratesErrors[i] = targetRate[i] - rates[i];
		}
                
                Serial.print("KP rate roll : ") ; Serial.println(kp_rate_roll);
                Serial.print("Rate errors : ") ; Serial.print(ratesErrors[0]); Serial.print(","); Serial.println(ratesErrors[1]);
                Serial.print("Control on"); Serial.println(CONTROL_ON);
                
		U2 = 1*CONTROL_ON*(kp_rate_roll * ratesErrors[0]);
		U3 = 1*CONTROL_ON*(kp_rate_roll * ratesErrors[1]);
	}
	

	//U1 = map_f(throttle, MAP_RADIO_LOW , MAP_RADIO_HIGH, 0, 80);
	U1 = throttle*0.10;
	U4=CONTROL_ON*0; //No Yaw control for the moment
	
        Serial.print("THROTTLE : ") ; Serial.println(throttle);

        Serial.print("U1 : "); Serial.println(U1);
        Serial.print("U2 : "); Serial.println(U2);
        Serial.print("U3 : "); Serial.println(U3);
        Serial.print("U4 : "); Serial.println(U4);
		

		
	//Roll is control by M2 and M4 via U2
	//Ptich is control by M1 and M3 via U3
		
	w2 = 1* (U1 + U2 + U4);   // 
	w1 = 1* (U1 + U3 - U4);   //
	w4 = 1* (U1 - U2 + U4);   //
	w3 = 1* (U1 - U3 - U4);   //

	if (w1<0) {
		w1=0;} 

	if (w2<0) {
		w2=0;}

	if (w3<0) {
		w3=0;}

	if (w4<0) {
		w4=0;} 


	if (  i_on)
	{
		i_max='1';
	}
	else
	{
		i_max='0';
	}

        Serial.print("1. Motor : ");
        Serial.println(1*w1);
        Serial.print("2. Motor : ");
        Serial.println(1*w2);
        Serial.print("3. Motor : ");
        Serial.println(1*w3);
        Serial.print("4. Motor : ");
        Serial.println(1*w4);
        Serial.println("Motor Speed PWM");
        Serial.print("1. Motor : ");
        Serial.println((1*w1*2) + MIN_MOTOR_SPEED_PWM);
        Serial.print("2. Motor : ");
        Serial.println((1*w2*2) + MIN_MOTOR_SPEED_PWM);
        Serial.print("3. Motor : ");
        Serial.println((1*w3*2) + MIN_MOTOR_SPEED_PWM);
        Serial.print("4. Motor : ");
        Serial.println((1*w4*2) + MIN_MOTOR_SPEED_PWM);
        
//        motors.setMotorSpeed(1, 1*w1);
//	motors.setMotorSpeed(2, 1*w2);
//	motors.setMotorSpeed(3, 1*w3);
//	motors.setMotorSpeed(4, 1*w4);

	counter_angle_loop++;
        Serial.print("Counter Angle Loop : "); Serial.println(counter_angle_loop);
}



