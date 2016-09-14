#ifndef LINETRACEMETHOD_H
#define LINETRACEMETHOD_H

#include "ColorSensor.h"
#include "PID.h"
#include "ev3api.h"
#include "BalancingWalker.h"
#include "GetLogData.h"
#include "Calibration.h"
#include "SonarAlert.h"


using namespace ev3api;

class LineTraceMethod {

private:
	ColorSensor* mColorSensor;
	PID* mPID;
	BalancingWalker* mBalancingWalker;
	Calibration* mCalibration;

	bool mIsInitialized;

	SonarAlert* mSonarAlert;

public:
	LineTraceMethod(ColorSensor* colorSensor,PID* pID,BalancingWalker* balancingWalker,Calibration* calibration,SonarAlert* sonarAlert);
	bool sonarFlag;
 void run(float p,float i,float d,int forward,int mix,int max,int offset);
	void SCENARIO_run();


	virtual ~LineTraceMethod();
};
#endif