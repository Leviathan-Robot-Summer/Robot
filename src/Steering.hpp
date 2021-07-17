#include <Arduino.h>
#include "Motor.hpp"

#define NORMAL_PWR 10

class Steering {
    Motor left;
    Motor right;

    public:
        Steering(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev);

        Steering();

        void setPins(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev);

        void start();
        /*
        amount -100 to 100 negatives are to go left and positives are to go right
        */
        void steer(int amount);

        void stop();
};
