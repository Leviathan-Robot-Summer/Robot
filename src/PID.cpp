#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "Position.cpp"
#include "Steering.cpp"

#define GOAL 0
#define maxI 0


/** Class that controls wheels and reads tape sensors
 * Uses PID controls to keep the sensors on the tape and moving foward
 * 
 * @author Lukas
 */ 
class TapeFollowing {
    int d, p, i, x, g, error = 0;
    int kp, ki, kd;
    int lasterr = 0; 
    Position pos;
    Steering Wheels;

    public:
        /** Creates a new tape following object
         * @param left_fwd: fwd pin for the left motor
         * @param left_rev: rev pin for the left motor
         * @param right_fwd: fwd pin for the right motor
         * @param right_rev: rev pin for the right motor
         * @param left_sensor: pin for the left IR sensor
         * @param right_sensor: pin for the right IR sensor
         * 
         * @author Lukas
         */ 
        TapeFollowing(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev, int left_sensor, int right_sensor) {
            pos.setSensors(left_sensor, right_sensor);
            Wheels.setPins(left_fwd, left_rev, right_fwd, right_rev);
        };

        /** Checks the IR sensors and steers the wheels to follow tape
         *  Loop in main to follow the tape 
         * 
         * @author Lukas
         */ 
        void followTape() {
            kp = 5; //analogRead(PA7) / 10; |
            ki = 0; //analogRead(PB0) / 10;  } these can be used  to turn the various values for 
            kd = 1; //analogRead(PB1) / 10; |

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


        /** Prints the positiond and some PID values to a display
         * @param display: the display object that values will be printed to 
         * 
         * @author Lukas
         */ 
        void showValues(Adafruit_SSD1306 display) {
            display.println(x);
            display.println(p);
            display.println(d);
            display.println(g);
            Wheels.showPower(display);
            //pos.showLR(display);
            
        }

        /** Stops both wheels
         * 
         * @author Lukas 
         */ 
        void stop() {
            Wheels.stop();
        }


};