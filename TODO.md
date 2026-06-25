# AutoChess-Displays TODO

- [x] Diagnose Reset-Ursache bei JC8048W550C + MicroChess Task
  - [x] Untersucht main.cpp: Chess Task läuft im separaten FreeRTOS Task, pinned to core
  - [x] Core-Wechsel (0/1) getestet -> keine Besserung
  - [x] MicroChess Code gelesen: engine läuft kontinuierlich und ruft in loop `show()` / `Serial` auf; kein offensichtliches Scheduler-Yield in der Engine-Schleife
  - [ ] Fix-Strategie wählen und implementieren
    - [ ] Test A: Periodisches `vTaskDelay(1)`/`delay(1)`/`taskYIELD()` im Chess Task einbauen (minimal invasive Änderung in main.cpp, soweit möglich)
    - [ ] Test B (fallback): Engine-Ausgabe deaktivieren (`game.options.print_level`) und `show()`/`set_led_strip()` aus MicroChess aussschalten bzw. nur im Arduino-Loop rendern
- [ ] Flash & Test: prüfen ob resets stoppen
- [ ] Falls weiter: Watchdog/ISR-Starvation weiter eingrenzen (Task-CPU-Last, Priority, Stack)


