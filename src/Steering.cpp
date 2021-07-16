#include <stdio.h>
#include <Arduino.h>

#define MOTORFREQ 1000
#define BASESPEED 1500
#define MOTOR_MAX 4096
#define MOTOR_MIN 2500 

#define NORMAL_PWR 10
class Motor {
    private:
        PinName fwd;
        PinName rev;
        int pwm_constant = (MOTOR_MAX - MOTOR_MIN) / 100; // MAX pwm divided by percentage


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
            if (power > 0) {
                pwm_start(fwd, MOTORFREQ, MOTOR_MIN + power * pwm_constant, RESOLUTION_12B_COMPARE_FORMAT);
                pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
            } else if (power < 0) {
                pwm_start(fwd, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
                pwm_start(rev, MOTORFREQ, MOTOR_MIN - power * pwm_constant, RESOLUTION_12B_COMPARE_FORMAT);
            } else {
                stop();
            }
        }

        void stop() {
            pwm_start(fwd, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
            pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
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

        void stop() {
            left.stop();
            right.stop();
        }
};
