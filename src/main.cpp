#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <lvgl.h>
#include "lvgl_project/ui.h"
#include "MicroChess/MicroChess.ino"

void chessTask(void * pvParameters) {
  setup_chess(); // Startet die unendliche Schach-Schleife isoliert auf Kern 0
}

void setup() {
  // put your setup code here, to run once:
  smartdisplay_init();
  ui_init();

  xTaskCreatePinnedToCore(
        chessTask,        /* Funktion des Tasks */
        "ChessTask",      /* Name */
        16384,            /* Ausreichend Stack-Speicher */
        NULL,             /* Parameter */
        1,                /* Niedrige Priorität */
        NULL,             /* Task-Handle */
        0                 /* Kern 0 */
  );
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x00FF00), LV_PART_MAIN);
    
    lv_timer_handler(); // Hält das GUI-Framework am Laufen
    delay(5);
}

