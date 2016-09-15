#include "RunMethod.h"

RunMethod::RunMethod(GyroSensor* gyroSensor,LineTraceMethod* lineTraceMethod,
  RemoteStart* remoteStart,Calibration* calibration,
  TailControl* tailControl,Clock* clock,TouchSensor* touchSensor,
  LookupMethod* lookupMethod,Stairs* stairs,Garage* g,SonarAlert* sonarAlert,gray_check* g_check2, Measure* mea2){

  mLineTraceMethod = lineTraceMethod;
  mRemoteStart = remoteStart;
  mCalibration = calibration;
  mTailControl = tailControl;
  mClock = clock;
  mState = UNDEFINED;
  mTouchSensor = touchSensor;
  mGyroSensor = gyroSensor;
  mLookupMethod = lookupMethod;
  mStairs = stairs;
  mSonarAlert = sonarAlert;
  gar = g;
  g_check1 = g_check2;
  mea1 = mea2;

  tail = 95;
  tail_flag = false;
}

RunMethod::~RunMethod(){

  tail = 95;
  tail_flag = false;

}

void RunMethod::run(){
  switch(mState){
    case UNDEFINED: //キャリブレーション
    execUndefined();
    break;
    case WAITING_FOR_START: //スタート待ち
    execWaitingForStart();
    break;
    case LINE_TRACE: //ただのコース走行
    execLineTracing();
    break;
    case SCENARIO_TRACE: //難所走行
    execScenarioTracing();
    break;
    default:
    break;
}
}

/**
 * 未定義状態の処理
**/
 void RunMethod::execUndefined() {
  mCalibration->initCali();
  mTailControl->tail_control(tail,80,true);

  if(mCalibration->touch_counter == 3){
    mState = WAITING_FOR_START;
}

mClock->sleep(10);
}

/**
 * 開始待ち状態の処理
**/
 void RunMethod::execWaitingForStart() {

  mTailControl->tail_control(tail,20,true);

  if(mRemoteStart->remote_start()){
    mState = LINE_TRACE;
    Line_Trace_flag = 10;
    mClock->reset();
    tail = 0;
}
mClock->sleep(10);
}

/**
 * ライントレース状態の処理
**/
 void RunMethod::execLineTracing(){
  switch(Line_Trace_flag){
      case 0: //ここから走行スタート
          mTailControl->tail_control(tail,20,false);
          mLineTraceMethod->run(0.27, 0.0, 0.01,100,-100,100,0);
          
          if(mea1->point_x>200){
              Line_Trace_flag = 1;
              ev3_speaker_play_tone (480,100);
          }
          break;
      case 1:
          //mLineTraceMethod->run(0.86, 0.008, 0.032,70,-100,100,0);
          mLineTraceMethod->run(0.86, 0.008, 0.032,70,-100,100,0);
          if(mea1->point_y>20){
              Line_Trace_flag = 2;
              ev3_speaker_play_tone (480,100);
          }
          break;
      case 2:
          mLineTraceMethod->run(0.27, 0.0, 0.01,100,-100,100,0);
          if(mea1->point_y>150){
              Line_Trace_flag = 3;
              ev3_speaker_play_tone (480,100);
          }
          break;
      case 3:
          mLineTraceMethod->run(0.7, 0.005, 0.03,40,-40,40,0);
          if(mea1->point_x<200&&mea1->point_y<120){
              Line_Trace_flag = 4;
              ev3_speaker_play_tone (480,100);
          }
          break;
      case 4:
          mLineTraceMethod->run(0.86, 0.008, 0.032,70,-100,100,0);
          if(mea1->point_y>30){
              Line_Trace_flag = 5;
              ev3_speaker_play_tone (480,100);
          }
          break;
      case 5:
          mLineTraceMethod->run(0.6, 0.005, 0.03,50,-50,50,0);
          break;
      case 6:
          break;
      case 10:
           mTailControl->tail_control(tail,20,false);
           mLineTraceMethod->run(0.6, 0.005, 0.03,18,-18,18,0);
          if(g_check1->gray_checker(mCalibration->LIGHT_BLACK,mCalibration->LIGHT_WHITE)==0&&mea1->point_x>20){
              ev3_speaker_play_tone (480,100);
          }
          break;
          // mLineTraceMethod->run(0.27, 0.0, 0.01,120,-120,120,0);
          // mLineTraceMethod->run(0.86, 0.008, 0.032,70,-100,100,0);//p,i,d,forward,pidの最小値,pidの最大値/0.022
          // mLineTraceMethod->run(0.3, 0.005, 0.03,30,-30,30,-8);
          // mLineTraceMethod->run(0.3, 0.005, 0.03,18,-30,30,0);
      case -1: // ここからゴール後
    mTailControl->tail_control(tail,20,false);

    mLineTraceMethod->run(0.39, 0.0, 0.04,30,-30,30,0);

    if(mSonarAlert->alert()){
      mState = SCENARIO_TRACE;
      SCENARIO_flag = 1;
      mClock->reset();
  }



  break;

  case -2:

  mLineTraceMethod->run(0.40, 0.0, 0.00,18,-18,18,-1);
  mTailControl->tail_control(tail,20,false);


  if(mGyroSensor->getAnglerVelocity() <= -100 && mClock->now() >= 3000){

    mState = SCENARIO_TRACE;
    SCENARIO_flag = 3;

  }

break;

default:
break;
}
}

/**
 * ゴール後の処理
 */
 void RunMethod::execScenarioTracing(){

  switch(SCENARIO_flag){
    case 1:

    if(mClock->now() <= 3000){
        mLineTraceMethod->run(0.0, 0.0, 0.0,0,0,0,0);
        mTailControl->tail_control(85, 50, true);
    }else{
        mLookupMethod->run();
        SCENARIO_flag = 0;
    }
    break;

    case 2:
    gar->slowrun_stop();
    break;

    case 3:

    mStairs->run();
 break;

 default:

 mLineTraceMethod->SCENARIO_run();

 break;
}
}
