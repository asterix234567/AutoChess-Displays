#include <Arduino.h>
#include <Wire.h>
#include <TAMC_GT911.h>
#include <lvgl.h>

// Pins exakt nach deinem hochgeladenen JC8048W550C-Schaltplan:
#define TOUCH_SDA  19
#define TOUCH_SCL  45
#define TOUCH_INT  18  // TP INT
#define TOUCH_RST  38  // LCD RST

// Touch-Objekt für ein 800x480 Display erstellen
TAMC_GT911 ts = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, 800, 480);

// Die Callback-Funktion, die LVGL ständig abfragt
void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data) {
    ts.read(); // Hardware abfragen
    
    if (ts.isTouched) {
        data->state = LV_INDEV_STATE_PR; // Status: Gedrückt
        
        // Pixel-Koordinaten an LVGL übergeben
        data->point.x = ts.points[0].x;
        data->point.y = ts.points[0].y;
    } else {
        data->state = LV_INDEV_STATE_REL; // Status: Losgelassen
    }
}

// Initialisierungs-Funktion für den Touch
void init_touch_driver() {
    ts.begin();
    ts.setRotation(ROTATION_NORMAL); // Falls X/Y vertauscht sind, hier ROTATION_INVERTED o.ä. nutzen

    // Den Touch-Treiber offiziell bei LVGL registrieren
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read; // Verknüpfung zur Lese-Funktion
    lv_indev_drv_register(&indev_drv);
}