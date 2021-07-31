#include <Arduino.h>
#include <Servo.h>
#include "Collection.hpp"

#define DEFAULT_LEVEL 25
#define UPPER_LEVEL 65
#define LOWER_LEVEL 110 //35 degrees more than UPPER_LEVEL

#define DISLODGE_DEFAULT 0
#define DISLODGE_KICK 45

#define DUMPER_DEFAULT 0
#define DUMPER_RELEASED 45


// Constructor initializes numberOfCans to 0 and assigns pins for the servo
// and microswitch.
Collection::Collection(int SERVO_CAN_SORTER, int DISLODGER, int DUMPER) {
    numberOfCans = 0;
    servoPin = SERVO_CAN_SORTER;
    dislodgerPin = DISLODGER;
    dumperPin = DUMPER;
}

void Collection::begin() {
    sortingFlap.attach(servoPin);
    sortingFlap.write(DEFAULT_LEVEL);
    dislodger.attach(dislodgerPin);
    dislodger.write(DISLODGE_DEFAULT);
    dumper.attach(dumperPin);
    dumper.write(DUMPER_DEFAULT);
    }

// This function is run as an interrupt from setup each time the microswitch for 
// can-counting is pressed. If the number of cans is less than 3, the sortingFlap goes
// to the upper level, lower level otherwise. Increments number of cans afterwards.
// For proper robot operation, should run returnToNormal() after a small delay.
void Collection::checkPin() {
    
    if (numberOfCans < 3) {
        sortingFlap.write(UPPER_LEVEL);
    }
    else {
        sortingFlap.write(LOWER_LEVEL);
    }
    //digitalWrite(PB10, HIGH);
    numberOfCans++;
}


// This function returns the sortingFlap to default level. Seperated from checkPin() in order to
// simulate multithreading. 
// Instead of adding a delay with delay(), we just run the normal loop x number of times to artificially create
// a delay. Then, we return the sortingFlap to default in a seperate function.
void Collection::returnToNormal() {
    sortingFlap.write(DEFAULT_LEVEL);
    digitalWrite(PB10, LOW);
}

// Rotates the servo so as to push the can to the correct place.
void Collection::dislodge() {
    dislodger.write(DISLODGE_KICK);
}

// Returns the dislodge servo to the default position.
void Collection::lodge() {
    dislodger.write(DISLODGE_DEFAULT);
}

// Returns the dumping servo to the released position.
void Collection::dump() {
    dumper.write(DUMPER_RELEASED);
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