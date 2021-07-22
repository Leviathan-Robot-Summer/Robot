#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "TapeFollowing.hpp"

#define GOAL 0
#define maxI 200

int d, p, i, x, g, error = 0;
int lasterr = 0; 

TapeFollowing::TapeFollowing(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev, int left_sensor, int right_sensor) {
    pos.setSensors(left_sensor, right_sensor);
    Wheels.setPins(left_fwd, left_rev, right_fwd, right_rev);
}

void TapeFollowing::followTape() {
    kp = analogRead(PA7) / 10;
    ki = analogRead(PB0) / 10;
    kd = analogRead(PB1) / 10;
    x = pos.getXValue();
    error = x;
    p = kp * error;
    d = kd*(error - lasterr);
    i += ki *error;
    if (i > maxI){ i = maxI;}
    if (i < -1*maxI){i = -maxI;}
    g = p + d + i;
    lasterr = error;
    
    Wheels.steer(g);
}

void TapeFollowing::showValues(Adafruit_SSD1306 display) {
    display.println(x);
    display.println(error);
    display.println(kp);
    display.println(ki);
    display.println(kd);
    display.println(g);
    pos.showLR(display);
}

void TapeFollowing::stop() {
    Wheels.stop();
}
