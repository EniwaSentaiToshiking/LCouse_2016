#include "GetLogData.h"

GetLogData::GetLogData(){

    gyrofile = fopen("gyrodata.txt","w");
    colorfile = fopen("colordata.txt","w");

    point_x = fopen("point_x.text","w");//座標データ
    point_y = fopen("point_y.text","w");
}

GetLogData::~GetLogData(){

 fclose(gyrofile);   /*logging file*/
 fclose(colorfile);  /*logging file*/
 fclose(point_x);//座標データファイル閉じる
 fclose(point_y);
}

void GetLogData::create_logFile(int16_t gyro,int8_t color,Measure *mea){

   //fprintf(point_x,"%f\n",mea->point_x);
    //fprintf(point_y,"%f\n",mea->point_y);

	fprintf(gyrofile,"%d\n",gyro);       /*logging data of gyro*/
    fprintf(colorfile,"///%d",color);    /*logging data of color*/

}