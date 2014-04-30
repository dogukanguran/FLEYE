/*
  taken from github.
*/
#ifndef Utils_h
#define Utils_h

#include "Arduino.h"
//#define rac22 0.7071

float getRac22();
float constrain_f(float x, float min, float max);
float map_f(float  x, float  in_min, float in_max, float out_min, float out_max);
float mean(int , float[]);
void isort(int *, byte);
int findMedian(int *, byte);
float filterSmooth(float, float, float);
int8_t sgn(int);

#endif
