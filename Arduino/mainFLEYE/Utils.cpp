/*
  taken from github.
 */
#include "Arduino.h"


float getRac22(){
  return 0.7071;
}

float map_f(float  x, float  in_min,float   in_max, float  out_min, float  out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mean(int m, float a[]){
  int sum=0, i;
  for(i=0; i<m; i++)
    sum+=a[i];
  return((float)sum/m);
}

void isort(int *a, byte n){
  for (int i = 1; i < n; ++i){
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--){
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

int findMedian(int *data, byte arraySize){
  isort(data, arraySize);
  return data[arraySize/2];
}

// Low pass filter, kept as regular C function for speed
float filterSmooth(float currentData, float previousData, float smoothFactor){
  if (smoothFactor != 1.0) //only apply time compensated filter if smoothFactor is applied
    return (previousData * (1.0 - smoothFactor) + (currentData * smoothFactor)); 
  else
    return currentData; //if smoothFactor == 1.0, do not calculate, just bypass!
}

int8_t sgn(int val){
  if (val < 0) return -1;
  if (val==0) return 0;
  return 1;
}

float constrain_f(float x, float min, float max){
  if (x>max){
    return max;
  }
  if (x<min){
    return min;
  }
  else{
    return x;
  }
}




