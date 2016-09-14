#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "ev3api.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "UI.h"
#include "GyroSensor.h"

using namespace ev3api;

class Calibration {

private:
uint8_t LIGHT_GRAY;

char lcd_white[4];
char lcd_black[4];
char lcd_gray[4];

int prev_touch;

ColorSensor* m_ColorSensor;
TouchSensor* m_TouchSensor;
UI* m_UI;
GyroSensor* m_GyroSensor;

public:
	int touch_counter;
	Calibration(TouchSensor* gTouchSensor, ColorSensor* gColorSensor, UI* gUI,GyroSensor* gyroSensor);
	void initCali();
	uint8_t calc_avarage_color();
	uint8_t LIGHT_WHITE;           
    uint8_t LIGHT_BLACK;
	virtual ~Calibration();
};
#endif