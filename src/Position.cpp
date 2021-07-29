#include <stdio.h>
#include <Arduino.h>
#include <algorithm>
#include <Adafruit_SSD1306.h>
#include "Position.hpp"

#define THRESHOLD 500 //separation between black and white sensor readings
#define SEPERATION 7 //separation width of the 2 sensors
#define DERIVATIVE_CONST 75 //constant to make sure the derivative isn't 0 from int division.

int current_index = 0;

int no_change = 0; //Stores how long there has been no change for


/** Initializes a new position object  without and variables assigned
 *  
 *  @author Lukas
 */
Position::Position(int left_sensor, int right_sensor) {
     right_sens = right_sensor;
     left_sens = left_sensor;
};

Position::Position() {};


/** Assigns @param left_sensor and @param right_sensor pin to this object's left and right sensors respectively
 *  
 * @author Lukas
 */ 
void Position::setSensors(int left_sensor, int right_sensor) {
    right_sens = right_sensor;
    left_sens = left_sensor;
}

/** Reads from the sensors and returns an x value
 *  
 * @author Lukas
 */
int Position::read() {
    rl = analogRead(left_sens);
    rr = analogRead(right_sens);
    r = rr > THRESHOLD;
    l = rl > THRESHOLD;
    if (r && l) {
        x = 0;
    } else if (r) {
        x = 2;
    } else if (l) {
        x = -2;
    } else {
        if (last > 0) {
            x = SEPERATION;
        } else if (last < 0) {
            x = -SEPERATION;
        } else {
            x = 100;  //TODO Always turn left?
        }
    }
    if (x == last) {
        no_change++; //used for derivative so when the value changes we get a sharp spike then
    } else {         //it inversely decays
        last_state = last;
        last_state_length = no_change;
        no_change = 0;
    }
    last = x;
    return x;
}

/** Prints the right and left reading values to the given display
 *  
 * @param display: the display object values are printed to
 * @author Lukas
 */ 
void Position::showLR(Adafruit_SSD1306 display) {
    display.println(rr);
    display.println(rl);
}


/** Returns the X value of the sensors
 *  
 *  @author Lukas
 */
int Position::getXValue() {
    return read();
}

/** Returns the approximated derivative of x
 *  change last change in x divided by how many times that and the previous reading have been read continously 
 *  
 *  @author Lukas
 */
int Position::getDerivative() {
    return (DERIVATIVE_CONST * (x - last_state)) / (no_change + last_state_length);
}

//test comment

