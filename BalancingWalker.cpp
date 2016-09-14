#include "BalancingWalker.h"

// 定数宣言
const int BalancingWalker::LOW    = 30;    // 低速
const int BalancingWalker::NORMAL = 70;    // 通常
const int BalancingWalker::HIGH   = 120;    // 高速


/**
 * コンストラクタ
 * @param gyroSensor ジャイロセンサ
 * @param leftMotor  左モータ
 * @param rightMotor 右モータ
 * @param balancer   バランサ
 */
 BalancingWalker::BalancingWalker(const GyroSensor* gyroSensor,
   Motor* leftMotor,
   Motor* rightMotor,
   Balancer* balancer){
  mGyroSensor = gyroSensor;
  mLeftMotor = leftMotor;
  mRightMotor = rightMotor;
  mBalancer = balancer;
  mForward =LOW;
  mTurn = LOW;
  mOffset = 0;
}

/**
 * デストラクタ
 */
 BalancingWalker::~BalancingWalker() {
 }

/**
 * バランス走行する
 */
 void BalancingWalker::run() {
    int16_t angle = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値
    int rightMotorEnc = mRightMotor->getCount();       // 右モータ回転角度
    int leftMotorEnc  = mLeftMotor->getCount();        // 左モータ回転角度

    mBalancer->setCommand(mForward, mTurn, mOffset);

    int battery = ev3_battery_voltage_mV();
    mBalancer->update(angle, rightMotorEnc, leftMotorEnc, battery);

    // 左右モータに回転を指示する
    mLeftMotor->setPWM(mBalancer->getPwmLeft());
    mRightMotor->setPWM(mBalancer->getPwmRight());
  }

void BalancingWalker::SCENARIO_run(bool flag){

// 左右モータに回転を指示する
  if(flag){
    mRightMotor->setPWM(9);
    mLeftMotor->setPWM(4);
    }else{
      mRightMotor->setPWM(4);
      mLeftMotor->setPWM(9);
}
}

/**
 * バランス走行に必要なものをリセットする
 */
 void BalancingWalker::init() {
  int offset = -1;

    //スピード70の時オフセット12
    //  // ジャイロセンサ値

    // モータエンコーダをリセットする
  mLeftMotor->reset();
  mRightMotor->reset();

    // 倒立振子制御初期化
  mBalancer->init(offset);
}

/**
 * PWM値を設定する
 * @param forward 前進値
 * @param turn    旋回値
 */
 void BalancingWalker::setCommand(int forward, int turn, int offset) {
  mForward = forward;
  mTurn    = turn;
  mOffset = offset;
}
