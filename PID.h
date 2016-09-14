#ifndef PID_H
#define PID_H

#include "ColorSensor.h"

class PID {

private:
	float KP;
	float KI;
	float KD;
	int diff[2];
	float integral;
	float DELTA_T;
    FILE *pid_data;

public:
	PID();
	int calcPID(float p_value,float i_value ,float d_value,unsigned int sensor_val,unsigned int target_val,int min,int max);
	int math_limit(int pid_value,int min,int max);

	virtual ~PID();
};
#endif