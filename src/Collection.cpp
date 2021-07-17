#include <Arduino.h>
#include <Servo.h>
#include "Collection.hpp"

#define LOWER_ANGLE 10
#define HIGHER_ANGLE 40

// Constructor initializes numberOfCans to 0 and assigns pins for the servo
// and microswitch.
Collection::Collection(int CAN_COUNTER, int SERVO_CAN_SORTER) {
    numberOfCans = 0;
    counterPin = CAN_COUNTER;
    servoPin = SERVO_CAN_SORTER;
}

void Collection::begin() {
    sortingFlap.attach(servoPin);
    sortingFlap.write(15);
}

// This function is run as an interrupt from setup each time the microswitch for 
// can-counting is pressed. It increments @numberOfCans; and moves the
// flap once numberOfCans >= 3.
void Collection::checkPin() {
    numberOfCans++;
    if (numberOfCans >= 3) {
        sortingFlap.write(45);
    }
}

int Collection::getCanAmount() {
    return numberOfCans;
}