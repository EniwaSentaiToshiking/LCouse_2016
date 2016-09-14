#ifndef TailControl_H
#define TailControl_H

#include "Motor.h"

using namespace ev3api;

class TailControl {
private:
	Motor* mTailMotor;
	int prev_tail;

public:
	TailControl(Motor* tailMotor);
	void tail_control(int tail,uint32_t speed,bool block);

	virtual ~TailControl();
};
#endif