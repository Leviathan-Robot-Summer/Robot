#include <Arduino.h>
#include <Servo.h>
#include "Collection.hpp"

#define DEFAULT_LEVEL 0
#define UPPER_LEVEL 45 
#define LOWER_LEVEL 80 //35 degrees more than UPPER_LEVEL
#define TIME_TO_FALL 1000 

// Constructor initializes numberOfCans to 0 and assigns pins for the servo
// and microswitch.
Collection::Collection(int CAN_COUNTER, int SERVO_CAN_SORTER) {
    numberOfCans = 0;
    counterPin = CAN_COUNTER;
    servoPin = SERVO_CAN_SORTER;
}

void Collection::begin() {
    sortingFlap.attach(servoPin);
    sortingFlap.write(DEFAULT_LEVEL);
}

// This function is run as an interrupt from setup each time the microswitch for 
// can-counting is pressed. If the number of cans is less than 3, the sortingFlap goes
// to the upper level, lower level otherwise. Then it waits a bit and goes back to default
// level. Increments number of cans afterwards.
void Collection::checkPin() {
    if (numberOfCans < 3) {
        sortingFlap.write(UPPER_LEVEL);
    }
    else {
        sortingFlap.write(LOWER_LEVEL);
    }
    delay(TIME_TO_FALL);
    sortingFlap.write(DEFAULT_LEVEL);
    numberOfCans++;
}

int Collection::getCanAmount() {
    return numberOfCans;
}

// test function used to manually test the correct servo angles.
// if selection == 0, sortingFlap goes to DEFAULT_LEVEL.
// if selection == 1, sortingFlap goes to UPPER_LEVEL.
// if selection == 2, sortingFlap goes to LOWER_LEVEL.
void Collection::switchManually(int selection) {
    switch (selection) {
        case 0:
            sortingFlap.write(DEFAULT_LEVEL);
            break;
        case 1:
            sortingFlap.write(UPPER_LEVEL);
            break;
        case 2:
            sortingFlap.write(LOWER_LEVEL);
            break;
    }
}