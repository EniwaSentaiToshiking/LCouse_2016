#include "Stairs.h"

Stairs::Stairs(const GyroSensor* gyroSensor, Motor* leftMotor,
	Motor* rightMotor, TailControl* tailControl,
	Clock* clock,BalancingWalker* balancingWalker, LineTraceMethod* lineTraceMethod){

	mGyroSensor = gyroSensor;
	mRightMotor = rightMotor;
	mLeftMotor = leftMotor;
	mTailControl = tailControl;
	mClock = clock;
	mBalancingWalker = balancingWalker;
	mLineTraceMethod = lineTraceMethod;
	stairsFlag = 0;
}

Stairs::~Stairs() {}

void Stairs::run(){

	mClock->reset();

	while(stairsFlag != -1){
		switch(stairsFlag){
			case 0:

			mLineTraceMethod->run(0.0, 0.0, 0.0,-10,-10,10,2);

			if(mClock->now() >= 1000){
				stairsFlag = 1;
			}

			break;

			case 1:


			break;



			case 2:



			mClock->wait(2000);

			stairsFlag = 3;

			break;

case 3:

break;

			default:
			stairsFlag = -1;
			break;
		}
		mClock->sleep(4);
	}
}