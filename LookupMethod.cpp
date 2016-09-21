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
    lookupFlag = 2;
    sonarFlag = false;
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
                
                mTailControl->tail_control(85, 50, false);
                
                
                mLeftMotor->setPWM(15);
                mRightMotor->setPWM(15);
                
                mClock->wait(300);
                
                mLeftMotor->setPWM(0);
                mRightMotor->setPWM(0);
                
                mClock->wait(1000);
                
                lookupFlag = 3;
                
                
                break;
                
            case 3:
                
                for(int i = 84; i >= 60; i--){
                    mTailControl->tail_control(i,10,true);
                    
                    mClock->sleep(300);
                    
                }
                
                lookupFlag = 4;
                
            case 4:
                mLeftMotor->setPWM(10);
                mRightMotor->setPWM(10);
                
                mClock->wait(2700);
                
                mLeftMotor->setPWM(0);
                mRightMotor->setPWM(0);
                
                mClock->wait(1000);
                
                
                mLeftMotor->setPWM(-10);
                mRightMotor->setPWM(-10);
                
                mClock->wait(3800);
                
                mLeftMotor->setPWM(0);
                mRightMotor->setPWM(0);
                
                mClock->wait(1000);
                
                
                mLeftMotor->setPWM(10);
                mRightMotor->setPWM(10);
                
                mClock->wait(3300);

                 mLeftMotor->setPWM(0);
                mRightMotor->setPWM(0);
                
                mClock->wait(500);
                
                lookupFlag = 6;
                
                break;
                
            case 6:
                
                mTailControl->tail_control(65, 100, true);
                mClock->wait(1000);
                
                mTailControl->tail_control(70, 50, true);
                mClock->wait(1000);
                
                mTailControl->tail_control(75, 50, true);
                mClock->wait(1000);
                
                
                for(int i = 76; i <= 93; i++){
                    mTailControl->tail_control(i,10,true);
                    
                    mClock->sleep(4);
                }
                
                
                lookupFlag = 7;
                
                break;
                
                
            case 7:
                ev3_speaker_play_tone (880,100);
                
                lookupFlag = 8;
                break;
                
                
            case 8:
                
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
