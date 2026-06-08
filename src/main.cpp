#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <lvgl.h>
#include "lvgl_project/ui.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  smartdisplay_init();
  ui_init();

  //auto display = lv_display_get_default();
  // lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
  // lv_display_set_rotation(display, LV_DISPLAY_ROTATION_180);
  // lv_display_set_rotation(display, LV_DISPLAY_ROTATION_270);
}

void colour_select() {
  
}
void loop() {
  // put your main code here, to run repeatedly:
  //lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x00FF00), LV_PART_MAIN);
    
    lv_timer_handler(); // Hält das GUI-Framework am Laufen
    delay(5);
}
