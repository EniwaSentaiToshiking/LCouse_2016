#include "TailControl.h"

TailControl::TailControl(Motor* tailMotor){
	mTailMotor = tailMotor;

	prev_tail = 0;

}

TailControl::~TailControl() {
}

void TailControl::tail_control(int tail,uint32_t speed,bool block){
	if(tail != prev_tail){
		ev3_motor_rotate(EV3_PORT_A,tail-mTailMotor->getCount(),speed,block);
	}
	prev_tail = tail;
}
