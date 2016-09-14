#ifndef GET_LOG_DATA_H
#define GET_LOG_DATA_H

#include "ev3api.h"
#include <stdio.h>
#include "Measure.h"

class GetLogData {
private:
FILE *gyrofile;      /*logging gyrosensor*/
FILE *colorfile;     /*logging colorsensor*/
FILE *point_x; //座標データ
FILE *point_y;

public:
	GetLogData();
	void create_logFile(int16_t gyro,int8_t color,Measure* mea);

	virtual ~GetLogData();
};
#endif