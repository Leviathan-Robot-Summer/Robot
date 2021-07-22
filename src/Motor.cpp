#include "Motor.hpp"

#define MOTORFREQ 1000
#define MOTOR_MAX 4096
#define MOTOR_MIN 2100
#define BASESPEED 1500 

#define NORMAL_PWR 10
#define MAX_PWR_FWD 50

int pwm_constant = (MOTOR_MAX - MOTOR_MIN) / 100;
int pwr = NORMAL_PWR;

Motor::Motor(PinName fwd, PinName rev) {
            fwd = fwd;
            rev = rev;
}

Motor::Motor() {}

void Motor::set_pins(PinName fwd_pin, PinName rev_pin) {
    fwd = fwd_pin;
    rev = rev_pin;
}

void Motor::power(int power) { //+ is forward and - is reverse in range [-100, 100]
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

void Motor::stop() {
    pwm_start(fwd, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
}

int Motor::getPower(){
    return pwr;
}