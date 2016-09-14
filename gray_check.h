#include "ColorSensor.h"
#ifndef gray_check_H
#define gray_check_H

using namespace ev3api;

class gray_check {
  private:
  int color;//取得した輝度値
  float average=0.0;//輝度値の平均
  float limit=5.3;//閾値
  int data[150]={};//保存データ
  int data_no=0;//データ番号
  int data_max=149;//データの最後の番号
  int sum;//保存データの合計
  int i;
  int count=0;
  ColorSensor* m_ColorSensor;
  FILE *get_colorfile;
  FILE *averagefile;
 public:
  gray_check(ColorSensor* g_ColorSensor);
  int gray_checker(uint8_t black, uint8_t white);
  virtual ~gray_check();
};

#endif
