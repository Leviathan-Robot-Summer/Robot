#include <Arduino.h>
#include <Servo.h>
#include "Collection.hpp"

#define UPPER_LEVEL 75
#define LOWER_LEVEL 120

// Constructor initializes numberOfCans to 0 and assigns pins for the servo
// and microswitch.
Collection::Collection(int CAN_COUNTER, int SERVO_CAN_SORTER) {
    numberOfCans = 0;
    counterPin = CAN_COUNTER;
    servoPin = SERVO_CAN_SORTER;
}

void Collection::begin() {
    sortingFlap.attach(servoPin);
    sortingFlap.write(UPPER_LEVEL);
}

// This function is run as an interrupt from setup each time the microswitch for 
// can-counting is pressed. It increments @numberOfCans; and moves the
// flap once numberOfCans >= 3.
void Collection::checkPin() {
    numberOfCans++;
    if (numberOfCans >= 3) {
        sortingFlap.write(LOWER_LEVEL);
    }
}

int Collection::getCanAmount() {
    return numberOfCans;
}

void Collection::switchLower() {
    sortingFlap.write(LOWER_LEVEL);
}