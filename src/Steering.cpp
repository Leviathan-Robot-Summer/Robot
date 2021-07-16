#include <stdio.h>
#include <Arduino.h>
#include "Steering.hpp"

#define NORMAL_PWR 10

Steering::Steering(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
    left.set_pins(left_fwd, left_rev);
    right.set_pins(right_fwd, right_rev);
    //left(left_fwd, left_rev);
    //left = &left_mot;
    //right(right_fwd, right_rev);
    //right = &right_mot;
};

Steering::Steering() {}

void Steering::setPins(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
    left.set_pins(left_fwd, left_rev);
    right.set_pins(right_fwd, right_rev);
    //left(left_fwd, left_rev);
    //left = &left_mot;
    //right(right_fwd, right_rev);
    //right = &right_mot;
};

void Steering::start() {
    left.power(NORMAL_PWR);
    right.power(NORMAL_PWR);
}

/*
amount -100 to 100 negatives are to go left and positives are to go right
*/
void Steering::steer(int amount) {
    right.power(NORMAL_PWR + amount);
    left.power(NORMAL_PWR - amount);                   
}

void Steering::stop() {
    left.stop();
    right.stop();
}

