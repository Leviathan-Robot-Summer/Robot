#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "TapeFollowing.hpp"

#define GOAL 0
#define maxI 0

int d, p, i, x, g, error = 0;
int lasterr = 0; 

TapeFollowing::TapeFollowing(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev, int left_sensor, int right_sensor) {
    pos.setSensors(left_sensor, right_sensor);
    Wheels.setPins(left_fwd, left_rev, right_fwd, right_rev);
}

void TapeFollowing::followTape() {
    kp = 5 ;//analogRead(PA7) / 10;
    ki = 0; //analogRead(PB0) / 10;
    kd = 1;
    
    x = pos.getXValue();
    error = x;
    p = kp * error;
    d = kd*pos.getDerivative();
    i += ki *error;
    i = 0;
    //if (i > maxI){ i = maxI;}
    //if (i < -1*maxI){i = -maxI;}
    g = p + d + i;
    lasterr = error;
    /*if (g != 0) {Wheels.steer(g);}
    else if (Wheels.direction() == 0) {
        if (pos.no_change % 100 == 0) {
            Wheels.increaseFwdSpeed();
        }
    } else {Wheels.stop();}*/
    Wheels.steer(g);
}

void TapeFollowing::showValues(Adafruit_SSD1306 display) {
    display.println(x);
    display.println(p);
    display.println(d);
    display.println(g);
    Wheels.showPower(display);
    //pos.showLR(display);
    
}

void TapeFollowing::stop() {
    Wheels.stop();
}
