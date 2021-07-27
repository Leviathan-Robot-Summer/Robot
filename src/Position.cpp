#include <stdio.h>
#include <Arduino.h>
#include <algorithm>
#include <Adafruit_SSD1306.h>

#define THRESHOLD 525 //seperation between black and white sensor readings
#define SEPERATION 7 //Spereation width of the 2 sensors

/** Abstraction of the position of the robot relative to the black line its following
 *  Useful for getting an "x" value which is defined as having the black line at x = 0
 *  Left side is + and right is -
 * 
 *  @author Lukas
 */
class Position {
    int last_state;
    int current_index = 0;
    
    public:
        int left_sens; //left pin 
        int right_sens; //right pin
        int x; //current position of the object
        int no_change = 0; //Stores how long there has been no change for
        bool r, l; // Binary interpretations of the left and right sensors
        int rr, rl; // Read values directly from the sensor
        int last; // The previous value of x (last != x)
        
        /** Creates a new position object and assigns @param left_sensor and @param right_sensor pin to 
         * this object's left and right sensors respectively
         * 
         * @author Lukas
         */ 
        Position(int left_sensor, int right_sensor) {
            right_sens = right_sensor;
            left_sens = left_sensor;
        };

        /** Initializes a new position object  without and variables assigned
         *  
         *  @author Lukas
         */
        Position() {};

        /** Assigns @param left_sensor and @param right_sensor pin to this object's left and right sensors respectively
         *  
         * @author Lukas
         */ 
        void setSensors(int left_sensor, int right_sensor) {
            right_sens = right_sensor;
            left_sens = left_sensor;
        }

        /** Reads from the sensors and returns an x value
         *  
         * @author Lukas
         */
        int read() {
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
                    x = 100;
                }
            }
            if (x == last) {
                no_change++; //used for derivative so when the value changes we get a sharp spike then
            } else {         //it inversely decays
                no_change = 0;
                last_state = last;
            }
            last = x;
            return x;
        }

        /** Prints the right and left reading values to the given display
         *  
         * @param display: the display object values are printed to
         * @author Lukas
         */ 
        void showLR(Adafruit_SSD1306 display) {
            display.println(rr);
            display.println(rl);
        }

        /** Returns the X value of the sensors
         *  
         *  @author Lukas
         */
        int getXValue() {
            return read();
        }

        /** Returns the approximated derivative of x
         *  change last change in x divided by how many times that and the previous reading have been read continously 
         *  
         *  @author Lukas
         */
        int getDerivative() {
            return ((x - last_state)) / no_change;
        }
};
        
