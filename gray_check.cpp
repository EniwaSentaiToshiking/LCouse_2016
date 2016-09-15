#include "gray_check.h"

gray_check::gray_check(ColorSensor* g_ColorSensor) {
    m_ColorSensor = g_ColorSensor;
    get_colorfile = fopen("get_colorfile.txt","w");
    averagefile = fopen("averagefile.txt","w");
}

gray_check::~gray_check() {
    fclose(get_colorfile); 
    fclose(averagefile); 
}

int  gray_check::gray_checker(uint8_t black, uint8_t white){
    
    color =m_ColorSensor->getBrightness();
    data[data_no]=color;//輝度値代入
    sum=0;
    
    for(i=0;i<=data_max;i++){
        sum=sum+data[i];
    }//データの合計
    
    if(data_no==data_max){
        data_no=0;
    }else{
        data_no++;
    }//データの番号を増やす

    average=((float)sum/(float)data_max);//平均値求める

    //fprintf(get_colorfile,"%d\n",color);
    //fprintf(averagefile,"%f\n",average);

    if(average <= 16 && average >= 14){
      count++;
    }

    if(count == 50){
        ev3_speaker_play_tone (480,100);
    }

    if(-((float)color-average)>limit&&color < 14&&count>=50){//取得した輝度値（黒）-平均値（灰色）>閾値,color<灰色,count>灰色をとる時間
        return 0;//灰色検知した
    }else{
        return 1;//していない
    }
 
}
//color<(black+white)*0.3
