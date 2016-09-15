#include "LineTraceMethod.h"

LineTraceMethod::LineTraceMethod(ColorSensor* gColorSensor,PID* pID,BalancingWalker* balancingWalker,
      Calibration* calibration, SonarAlert* sonarAlert) {

  mColorSensor = gColorSensor;
  mPID = pID;
  mBalancingWalker = balancingWalker;
  mCalibration = calibration;
  mIsInitialized = false;

  mSonarAlert = sonarAlert;
  sonarFlag = false;

ev3_led_set_color(LED_GREEN); /*led*/
}

LineTraceMethod::~LineTraceMethod() {
}

void LineTraceMethod::run(float p, float i, float d,int forward,int min, int max,int offset){
  if (mIsInitialized == false) {
    mBalancingWalker->init();
    mIsInitialized = true;
  }

int turn = mPID->calcPID(p, i, d, mColorSensor->getBrightness(), mCalibration->calc_avarage_color(),min,max) * -1; //操作量
    /*スピード70のときp=0.84,i=0.005,d=0.022*/

//gGetLogData->create_logFile(gyro,color);
mBalancingWalker->setCommand(forward, turn,offset);
//mBalancingWalker->setCommand(20, turn, 0);



//距離センサ
// if ( mSonarAlert->alert() )
//   sonarFlag = true;
//   mBalancingWalker->setCommand(0, 0, 0);

//}

// 倒立走行を行う
mBalancingWalker->run();

}

void LineTraceMethod::SCENARIO_run(){

if(mColorSensor->getBrightness() >= mCalibration->calc_avarage_color()){
  mBalancingWalker->SCENARIO_run(true);
}else{
  mBalancingWalker->SCENARIO_run(false);
}



}