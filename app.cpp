//////app.cpp///////

#include "ev3api.h"
#include "app.h"

#include "RunMethod.h"
#include "SonarAlert.h"
#include "gray_check.h"

using namespace ev3api;

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define DEBUG
#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/*Using Sensor API*/
TouchSensor*    touchSensor;
SonarSensor*    sonarSensor;
ColorSensor*    colorSensor;
GyroSensor*     gyroSensor;
Motor*          leftMotor;
Motor*          rightMotor;
Motor*          tailMotor;
Clock*          clock;

/*Using Original API*/
static RunMethod *gRunMethod;
static PID *gPID;
static SonarAlert *gSonarAlert;
static RemoteStart *gRemoteStart;
static TailControl *gTailControl;
static Calibration *gCalibration;
static UI *gUI;
static LineTraceMethod *gLineTraceMethod;
static GetLogData *gGetLogData;
static BalancingWalker *gBalancingWalker;
static LookupMethod *gLookupMethod;
static Stairs *gStairs;
static Balancer *gBalancer;

static Garage *gar;//ガレージ系
static Measure *mea;//距離
static gray_check *g_check;//灰色

static FILE *clockfile;

static void system_create(){

  /*Sensor Class(Port)*/
  touchSensor = new TouchSensor(PORT_1);
  colorSensor = new ColorSensor(PORT_3);
  sonarSensor = new SonarSensor(PORT_2);
  gyroSensor  = new GyroSensor(PORT_4);
  leftMotor   = new Motor(PORT_C);
  rightMotor  = new Motor(PORT_B);
  tailMotor   = new Motor(PORT_A);
  clock       = new Clock();

    /*Original Class*/
    //gPID = new PID(0.65,2.0,0.045);
gUI = new UI();                 /*pid control(P,I,D)*/
gPID = new PID(); //0.65,0.0,0.0
gSonarAlert = new SonarAlert(sonarSensor);                    /*the number of reactionning sonarsensor(int centimeter)*/
gTailControl = new TailControl(tailMotor);
gRemoteStart = new RemoteStart();
gCalibration = new Calibration(touchSensor,colorSensor,gUI,gyroSensor);
       /*(wait,stop,move,gain,maxing pwm)*/
gGetLogData = new GetLogData();
gBalancer = new Balancer();
gBalancingWalker = new BalancingWalker(gyroSensor,leftMotor,rightMotor,gBalancer);
gLineTraceMethod = new LineTraceMethod(colorSensor,gPID,gBalancingWalker,gCalibration,gSonarAlert);
gLookupMethod = new LookupMethod(gyroSensor,leftMotor,rightMotor,gTailControl,clock,gSonarAlert,gBalancingWalker);
gStairs = new Stairs(gyroSensor,leftMotor,rightMotor,gTailControl,clock,gBalancingWalker,gLineTraceMethod);
gar = new Garage(rightMotor, leftMotor, gTailControl, gBalancingWalker, clock, gyroSensor); //ガレージ系
g_check = new gray_check(colorSensor);//灰色
mea = new Measure(rightMotor,leftMotor);//距離

gRunMethod = new RunMethod(gyroSensor,gLineTraceMethod,gRemoteStart,gCalibration,gTailControl,clock,touchSensor,gLookupMethod,gStairs,gar,gSonarAlert,g_check,mea);
ev3_led_set_color(LED_ORANGE); /*初期化完了通知*/


   /*tailmotor*/
tailMotor->reset();
}

static void system_destroy() {
  leftMotor->reset();
  rightMotor->reset();
  tailMotor->reset();

  delete gPID;
  delete gSonarAlert;
  delete gRemoteStart;
  delete gTailControl;
  delete gCalibration;
  delete gUI;
  delete gLineTraceMethod;
  delete gGetLogData;
  delete gBalancer;
  delete gBalancingWalker;
  delete gLookupMethod;
  delete gStairs;
  delete gRunMethod;
  delete g_check;
  delete mea;
  delete gar;
  fclose(clockfile);
}

/**
 * トレース実行タイミング
 */
 void ev3_cyc_tracer(intptr_t exinf) {
  act_tsk(TRACER_TASK);
}

/*Main Task*/
void main_task(intptr_t unused)
{

  system_create();

  while(1){

  if(ev3_button_is_pressed(BACK_BUTTON)) break;

 if(gyroSensor->getAnglerVelocity() <= -350 || gyroSensor->getAnglerVelocity() >= 350){
  break;
  }

 /*距離測る*/
    mea->measure();
    
 gRunMethod->run();  // 倒立走行

tslp_tsk(4);
}



ter_tsk(TRACER_TASK);
system_destroy();
ext_tsk();
}

/**
 * ライントレースタスク
 */
 void tracer_task(intptr_t exinf) {
  if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
      }

      ext_tsk();
    }
  }