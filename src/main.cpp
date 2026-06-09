#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <lvgl.h>
#include "lvgl_project/ui.h"
#include "MicroChess/MicroChess.ino"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  smartdisplay_init();
  ui_init();
  setup_chess();
  
}

void colour_select() {
  
}
void loop() {
  // put your main code here, to run repeatedly:
  //lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x00FF00), LV_PART_MAIN);
    
    lv_timer_handler(); // Hält das GUI-Framework am Laufen
    delay(5);
}
