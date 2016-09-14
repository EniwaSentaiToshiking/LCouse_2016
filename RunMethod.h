
#ifndef RUNMETHOD_H
#define RUNMETHOD_H

#include "RemoteStart.h"
#include "LineTraceMethod.h"
#include "Calibration.h"
#include "TailControl.h"
#include "Clock.h"
#include "TouchSensor.h"
#include "LookupMethod.h"
#include "Stairs.h"
#include "ev3api.h"
#include "gray_check.h"
#include "Measure.h"
#include "Garage.h"
#include "SonarAlert.h"
#include "GyroSensor.h"
#include "Motor.h"

using namespace ev3api;

class RunMethod {

private:

enum State {
UNDEFINED,  //未定義
WAITING_FOR_START, //スタート待ち
LINE_TRACE,   //走行中
// LINE_TRACE2,   //走行中
// LINE_TRACE3,   //走行中
// LINE_TRACE4,   //走行中
// LINE_TRACE5,   //走行中
// LINE_TRACE6,   //走行中
SCENARIO_TRACE //難所
};

int tail;
bool tail_flag;
int Line_Trace_flag;
int SCENARIO_flag;

RemoteStart* mRemoteStart;
Calibration* mCalibration;
LineTraceMethod* mLineTraceMethod;
TailControl* mTailControl;
Clock* mClock;
State mState;
TouchSensor* mTouchSensor;
GyroSensor* mGyroSensor;
LookupMethod* mLookupMethod;
Stairs* mStairs;

SonarAlert* mSonarAlert;

Garage* gar;
gray_check* g_check1;
Measure* mea1;

void execUndefined();
    void execWaitingForStart();
    void execLineTracing();
    void execLineTracing2();
    void execLineTracing3();
    void execLineTracing4();
    void execLineTracing5();
    void execLineTracing6();
    void execScenarioTracing();

public:
	RunMethod(GyroSensor* gyroSensor,LineTraceMethod* lineTraceMethod,
		RemoteStart* remoteStart,
		Calibration* calibration,TailControl* tailControl,
		Clock* clock,TouchSensor* touchSensor,
		LookupMethod* lookupMethod,Stairs* stairs,Garage* g,SonarAlert* sonarAlert, gray_check* g_check2, Measure* mea2);
	void run();

	virtual ~RunMethod();

};

#endif