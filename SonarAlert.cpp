#include "SonarAlert.h"

SonarAlert::SonarAlert(SonarSensor* sonarSensor){
  mSonarSensor = sonarSensor;
  distance = 10;
}

SonarAlert::~SonarAlert() {
}

bool SonarAlert::alert(void){

  static uint32_t counter = 0;
  static bool alert = false;

    if (++counter == 40/4) /* 約40msec周期毎に障害物検知  */
    {
        /*
         * 超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
         * NXTの場合は、40msec周期程度が経験上の最短測定周期です。
         * EV3の場合は、要確認
         */
        distance = mSonarSensor->getDistance(); /* 距離の取得（API） */
        if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
        {
            alert = true; /* 障害物を検知 */
        }
        else
        {
            alert = false; /* 障害物無し */
        }
        counter = 0;
    }
    return alert;
}
