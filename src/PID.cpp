#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

#include "Position.cpp"
#include "Steering.cpp"

#define GOAL 0
#define maxI 0



class TapeFollowing {
    int d, p, i, x, g, error = 0;
    int kp, ki, kd;
    int lasterr = 0; 
    Position pos;
    Steering Wheels;

    public:
        TapeFollowing(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev, int left_sensor, int right_sensor) {
            pos.setSensors(left_sensor, right_sensor);
            Wheels.setPins(left_fwd, left_rev, right_fwd, right_rev);
        };

        void followTape() {
            kp = 5;//analogRead(PA7) / 10;
            ki = 0; //analogRead(PB0) / 10;
            kd = analogRead(PB1) / 10;
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

        void showValues(Adafruit_SSD1306 display) {
            display.println(x);
            display.println(p);
            display.println(d);
            display.println(g);
            Wheels.showPower(display);
            //pos.showLR(display);
            
        }

        void stop() {
            Wheels.stop();
        }


};