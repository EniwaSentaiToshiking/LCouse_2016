#include "Measure.h"

Measure::Measure(Motor* g_rightMotor,Motor* g_leftMotor){
    m_leftMotor=g_leftMotor;
    m_rightMotor=g_rightMotor;
}
Measure::~Measure(){
}

void Measure::measure(){
  r0=m_rightMotor->getCount();
  l0=m_leftMotor->getCount();

  anR=r0-r1;
  anL=l0-l1;//タイヤの回転角度
    
  TR=2*M_PI*R*(anR/360);
  TL=2*M_PI*R*(anL/360);//タイヤの進んだ距離
    
  D=(TR+TL)/2;//車体の進んだ距離
    
  w=(TR-TL)/(2*d);//旋回角度計算
    
  x1=x0+(D*cos(z0+(w/2)));
  y1=y0+(D*sin(z0+(w/2)));//現在の座標を求める
  z1=z0+w;//現在の角度を求める

  point_x=x1;
  point_y=y1;//現在の座標を実際に取得する値
  
  x0=x1;
  y0=y1;
  z0=z1;//座標の更新
  r1=r0;
  l1=l0;//エンコーダ値の更新
}

void Measure::distance_reset(){
    x0=0.0;
    y0=0.0;
    z0=0.0;
    r1=r0;
    l1=l0;
}//距離初期化