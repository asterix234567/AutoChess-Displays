#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <lvgl.h>

#include "ui/ui.h"

void setup() {
  Serial.begin(115200);

  smartdisplay_init();
  ui_init();
}

void loop() {
    lv_timer_handler(); 

    Serial.println("Loop läuft...");
    delay(1000);

    // 2. Unabhängig die Touch-Daten abfragen, die LVGL gerade ermittelt hat
    lv_indev_t* indev = lv_indev_get_next(NULL); // Holt das Eingabegerät (Touchscreen)
    Serial.printf("Device type: %d\n", indev->type);
    
    if (indev != NULL) {
        lv_point_t point;
        // Holt die aktuellen X/Y Koordinaten des Zeigers
        lv_indev_get_point(indev, &point); 

        // Prüfen, ob der Bildschirm im Moment aktiv berührt wird
        lv_indev_state_t state = lv_indev_get_state(indev);
        Serial.printf("Touch state: %d\n", state);
        if (state == LV_INDEV_STATE_PRESSED) {

            int16_t touch_x = point.x;
            int16_t touch_y = point.y;

            // Hier hast du deine exakten Pixel-Daten für das Schachspiel!
            Serial.printf("Touch erkannt! X: %d, Y: %d\n", touch_x, touch_y);
        }
    } else {
        Serial.println("Kein Eingabegerät gefunden!");
    }
    
    /*
    String touch = touch_calibration_data.valid ? "calibrated" : "not calibrated";
    Serial.println(touch);
    delay(1000);
    */
    delay(5);
}