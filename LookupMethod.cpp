#include "LookupMethod.h"

LookupMethod::LookupMethod(const GyroSensor* gyroSensor, Motor* leftMotor,
 Motor* rightMotor, TailControl* tailControl,
 Clock* clock, SonarAlert* sonarAlert,BalancingWalker* balancingWalker ){

  mGyroSensor = gyroSensor;
  mRightMotor = rightMotor;
  mLeftMotor = leftMotor;
  mTailControl = tailControl;
  mClock = clock;
  mSonarAlert = sonarAlert;
  mBalancingWalker = balancingWalker;
  lookupFlag = 1;
}

/**
 * デストラクタ
 */
 LookupMethod::~LookupMethod() {}


 void LookupMethod::run(){
//int16_t angle = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値
//int rightMotorEnc = mRightMotor->getCount();       // 右モータ回転角度
//int leftMotorEnc  = mLeftMotor->getCount();        // 左モータ回転角度

  while(lookupFlag != -1){
    switch(lookupFlag){

      case 1:

      mClock->reset();
      lookupFlag = 2;

      break;

      case 2:

      mTailControl->tail_control(85, 50, true);


      mLeftMotor->setPWM(9);
      mRightMotor->setPWM(7);

      mClock->wait(1000);

      mLeftMotor->setPWM(0);
      mRightMotor->setPWM(0);

      mClock->wait(1000);

      lookupFlag = 3;


      break;

      case 3:

      mTailControl->tail_control(80, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(75, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(70, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(67, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(65, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(62, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(60, 30, true);
      mClock->wait(1000);

      lookupFlag = 4;

      case 4:

      mLeftMotor->setPWM(10);
      mRightMotor->setPWM(10);

      mClock->wait(3500);

      mLeftMotor->setPWM(0);
      mRightMotor->setPWM(0);

      mClock->wait(1000);

      mLeftMotor->setPWM(-10);
      mRightMotor->setPWM(-10);

      mClock->wait(3500);


      mLeftMotor->setPWM(0);
      mRightMotor->setPWM(0);

      mClock->wait(500);


      mLeftMotor->setPWM(20); 
      mRightMotor->setPWM(20);

      mClock->wait(2000);

      mLeftMotor->setPWM(0);
      mRightMotor->setPWM(0);

      lookupFlag = 5;

      break;

      case 5:

      mTailControl->tail_control(65, 50, true);
      mClock->wait(1000);

      mTailControl->tail_control(70, 50, true);
      mClock->wait(1000);

      mTailControl->tail_control(75, 50, true);
      mClock->wait(1000);


      mTailControl->tail_control(78, 50, true);
      mClock->wait(1000);

      mTailControl->tail_control(80, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(83, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(85, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(86, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(87, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(88, 30, true);
      mClock->wait(1000);

      mTailControl->tail_control(89, 20, true);
      mClock->wait(1000);

      mTailControl->tail_control(90, 20, true);
      mClock->wait(1000);

      mTailControl->tail_control(91, 20, true);
      mClock->wait(1000);

      mTailControl->tail_control(92, 20, true);
      mClock->wait(1000);

      mTailControl->tail_control(93, 20, true);
      mClock->wait(1000);


      lookupFlag = 6;

      break;


      case 6:
      ev3_speaker_play_tone (880,100);

      lookupFlag = 7;
      break;


      case 7:

      lookupFlag = 0;

      break;

default: //姿勢を起こす
ev3_speaker_play_tone (880,100);
lookupFlag = -1;
break;
}

mClock->sleep(4);
}
}