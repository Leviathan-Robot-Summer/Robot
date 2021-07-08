#include <stdio.h>
#include <Arduino.h>

#define MOTORFREQ 1000
#define BASESPEED 2500

class Motor {
    PinName fwd;
    PinName rev;
    int pwm_constant = 1000 / 100; // MAX pwm divided by percentage

    public:
        Motor(PinName fwd, PinName rev) {
            fwd = fwd;
            rev = rev;
        }

        Motor() {
            fwd = PA_3;
            rev = PA_6;
        }

        void increase(int value) {
            if (value >= 0) {
                pwm_start(fwd, MOTORFREQ, BASESPEED + value, RESOLUTION_12B_COMPARE_FORMAT);
                pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
            } else {
                pwm_start(fwd, MOTORFREQ, BASESPEED - value, RESOLUTION_12B_COMPARE_FORMAT);
                pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
            }
        }
};


class Steering {
    Motor left;
    Motor right;

    public:
        Steering(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
            left(left_fwd, left_rev);
            //left = &left_mot;
            right(right_fwd, right_rev);
            //right = &right_mot;
        };

        void start() {
            *left.increase(0);
            *right.increase(0);
        }

        /*
        amount -100 to 100 negatives are to go left and positives are to go right
        */
        void steer(int amount) {
            if (amount > 0) {
                right.increase(amount * 10);
                left.increase(0);
            } else {
                right.increase(0);
                left.increase(amount * 10);
            }
        }
};
