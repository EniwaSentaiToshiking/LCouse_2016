#ifndef SonarAlert_H
#define SonarAlert_H

#include "SonarSensor.h"

#define SONAR_ALERT_DISTANCE 15  /* 超音波センサによる障害物検知距離[cm] */

using namespace ev3api;

class SonarAlert {
private:
	int16_t distance;
SonarSensor* mSonarSensor;


public:
	SonarAlert(SonarSensor* sonarSensor);
	bool alert(void);

	virtual ~SonarAlert();
};
#endif