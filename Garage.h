	#ifndef Gagare_H
	#define Garage_H

	#include "Motor.h"
	#include "TailControl.h"
	#include "BalancingWalker.h"
	#include "Clock.h"
	#include "GyroSensor.h"

using namespace ev3api;

class Garage{

private:
	Motor *rMotor;
	Motor *lMotor;
	TailControl *mTailControl;
	BalancingWalker *bw; 
	Clock *c;
	GyroSensor *gyro;
	int GARAGE_flag;

public:
	Garage(Motor* r, Motor* l, TailControl* tc, BalancingWalker* b, Clock* clock, GyroSensor* g);
	void slowrun_stop();
	virtual ~Garage();
	};

	#endif