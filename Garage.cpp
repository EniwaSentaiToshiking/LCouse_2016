#include "Garage.h"

Garage::Garage(Motor* r, Motor* l, TailControl* tc, BalancingWalker* b, Clock* clock, GyroSensor* g){
	rMotor = r;
	lMotor = l;
	mTailControl = tc;
    bw = b;
    c = clock;
    gyro = g;
    GARAGE_flag = 0;
}

Garage::~Garage(){
}

void Garage::slowrun_stop(){

	c->reset();
	
	while(GARAGE_flag <= 4)
		switch(GARAGE_flag){
			case 0: //バランスを取りながら走行
			// bw->setCommand(5,0,0);
			// bw->run();
			rMotor->setPWM(20);
			lMotor->setPWM(20);

		if(c->now() == 100){
  		GARAGE_flag=1;
  		c->reset();
		}

		break;

			case 1: //尻尾を出しながら少し傾く
			// bw->setCommand(0,0,-15);
			// bw->run();
			mTailControl->tail_control(85, 50, false);

			c->wait(4);

  			GARAGE_flag=2;

			break;

			case 2:

			rMotor->setPWM(10);
			lMotor->setPWM(10);

			if(c->now() >= 3200){
				rMotor->setBrake(true);
				lMotor->setBrake(true);

 				rMotor->setPWM(0);
				lMotor->setPWM(0);
			}
	}
}


