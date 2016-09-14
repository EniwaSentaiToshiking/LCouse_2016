#ifndef STAIRS_H
#define STAIRS_H

#include "GyroSensor.h"
#include "Motor.h"
#include "TailControl.h"
#include "Clock.h"
#include "BalancingWalker.h"
#include "LineTraceMethod.h"

using namespace ev3api;

class Stairs{

private:
  const GyroSensor* mGyroSensor;
  Motor* mLeftMotor;
  Motor* mRightMotor;
  TailControl* mTailControl;
  Clock* mClock;
  BalancingWalker* mBalancingWalker;
  LineTraceMethod* mLineTraceMethod;

  int stairsFlag;

public:
  Stairs(const GyroSensor* gyroSensor, Motor* leftMotor,
    Motor* rightMotor, TailControl* tailControl,Clock* clock,BalancingWalker* balancingWalker,LineTraceMethod* lineTraceMethod);
  void run();
  virtual ~Stairs();

};

#endif