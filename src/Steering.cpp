#include <stdio.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define MOTORFREQ 1000
#define BASESPEED 1500
#define MOTOR_MAX 4096
#define MOTOR_MIN 2100

#define NORMAL_PWR 10
#define MAX_PWR_FWD 50

class Motor {
    private:
        PinName fwd;
        PinName rev;
        int pwm_constant = (MOTOR_MAX - MOTOR_MIN) / 100; // MAX pwm divided by percentage
        int pwr = NORMAL_PWR;


    public:
        Motor(PinName fwd, PinName rev) {
            fwd = fwd;
            rev = rev;
        }

        Motor() {}

        void set_pins(PinName fwd_pin, PinName rev_pin) {
            fwd = fwd_pin;
            rev = rev_pin;
        }

        void power(int power) { //+ is forward and - is reverse in range [-100, 100]
            if (power > 100) {power = 100;}
            if (power < -100) {power = -100;}
            stop();
           // delay(5);
            if (power > 0) {
                pwm_start(fwd, MOTORFREQ, MOTOR_MIN + power * pwm_constant, RESOLUTION_12B_COMPARE_FORMAT);
            } else if (power < 0) {
                pwm_start(rev, MOTORFREQ, MOTOR_MIN - power * pwm_constant, RESOLUTION_12B_COMPARE_FORMAT);
            }
            pwr = power;
        }

        void stop() {
            pwm_start(fwd, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
            pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
        }

        int getPower() {
            return pwr;
        }
};


class Steering {
    Motor left;
    Motor right;

    public:
        Steering(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
            left.set_pins(left_fwd, left_rev);
            right.set_pins(right_fwd, right_rev);
            //left(left_fwd, left_rev);
            //left = &left_mot;
            //right(right_fwd, right_rev);
            //right = &right_mot;
        };

        Steering() {}

        void setPins(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
            left.set_pins(left_fwd, left_rev);
            right.set_pins(right_fwd, right_rev);
            //left(left_fwd, left_rev);
            //left = &left_mot;
            //right(right_fwd, right_rev);
            //right = &right_mot;
        };

        void start() {
            left.power(NORMAL_PWR);
            right.power(NORMAL_PWR);
        }

        /*
        amount -100 to 100 negatives are to go left and positives are to go right
        */
        void steer(int amount) {
            right.power(NORMAL_PWR + amount);
            left.power(NORMAL_PWR - amount);  
        }

        bool increaseFwdSpeed() {
            bool increased = false;
            if (right.getPower() == left.getPower()) {
                if (left.getPower() < MAX_PWR_FWD) {
                    left.power(1 + left.getPower());
                    right.power(1 + right.getPower());
                }
                increased = true;
            }
            return increased;
        }           
        
        int direction() {
            return left.getPower() - right.getPower();
        }

        void stop() {
            left.stop();
            right.stop();
        }

        void showPower(Adafruit_SSD1306 display) {
            display.println(left.getPower());
            display.println(right.getPower());
        }
};
