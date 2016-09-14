#include "UI.h"

UI::UI(){

 /*LCD*/
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
    ev3_lcd_draw_string("EV3way-ET 2015", 0, CALIB_FONT_HEIGHT*1);

   string_count = 2;

}

UI::~UI(){
}

void UI::lcdDraw(const char* string){


    ev3_lcd_draw_string(string, 0, CALIB_FONT_HEIGHT*string_count);

    string_count++;

}
