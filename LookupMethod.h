#ifndef LOOKUPMETHOD_H
#define LOOKUPMETHOD_H

#include "GyroSensor.h"
#include "Motor.h"
#include "TailControl.h"
#include "Clock.h"
#include "SonarAlert.h"
#include "BalancingWalker.h"

using namespace ev3api;

class LookupMethod{

private:
  const GyroSensor* mGyroSensor;
  Motor* mLeftMotor;
  Motor* mRightMotor;
  TailControl* mTailControl;
  Clock* mClock;
  SonarAlert* mSonarAlert;
BalancingWalker* mBalancingWalker;

int lookupFlag;
bool sonarFlag;

public:
  LookupMethod(const GyroSensor* gyroSensor, Motor* leftMotor,
    Motor* rightMotor, TailControl* tailControl,Clock* clock,
    SonarAlert* sonarAlert,BalancingWalker* balancingWalker);
  void run();

  virtual ~LookupMethod();


};

#endif