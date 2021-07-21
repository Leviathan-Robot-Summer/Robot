#include <Arduino.h>


void heartbeat(int LED) {
    while (true) {
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
    }
}