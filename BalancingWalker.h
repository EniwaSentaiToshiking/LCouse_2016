#ifndef EV3_UNIT_BALANCINGWALKER_H_
#define EV3_UNIT_BALANCINGWALKER_H_

#include "GyroSensor.h"
#include "Motor.h"
#include "BalancerCpp.h"

using namespace ev3api;

class BalancingWalker {
public:
    static const int LOW;
    static const int NORMAL;
    static const int HIGH;

    BalancingWalker(
        const GyroSensor* gyroSensor,
                    Motor* leftMotor,
                    Motor* rightMotor,
                    Balancer* balancer);
    virtual ~BalancingWalker();

    void init();
    void run();
    void SCENARIO_run(bool flag);
    void stay();
    void setCommand(int forward, int turn, int offset);

private:
    const GyroSensor* mGyroSensor;
    Motor* mLeftMotor;
    Motor* mRightMotor;
    Balancer* mBalancer;
    int mForward;
    int mTurn;
    int mOffset;
};

#endif  // EV3_UNIT_BALANCINGWALKER_H_
