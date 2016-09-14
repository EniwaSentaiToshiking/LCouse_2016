#include "PID.h"

PID::PID() {

	KP = 0;
	KI = 0;
	KD = 0;
	DELTA_T = 0.004;
  pid_data = fopen("pid","w");

}

PID::~PID() {
   fclose(pid_data);
}

int PID::calcPID(float p_value, float i_value, float d_value,unsigned int sensor_val,unsigned int target_val,int min,int max){

int p,i,d;
  KP = p_value;
  KI = i_value;
  KD = d_value;

  diff[0] = diff[1];
  diff[1] = sensor_val - target_val;
  integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;

  p = KP * diff[1];
  i = KI * integral;
  d = KD * (diff[1] - diff[0]) /DELTA_T;

  return math_limit(p + i + d, min, max);

}

int PID::math_limit(int pid_value,int min,int max){

if(pid_value > max) pid_value = max;
  else if(pid_value < min) pid_value = min;
   fprintf(pid_data,"%d\n",pid_value);
  return pid_value;
}