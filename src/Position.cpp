#include <stdio.h>
#include <Arduino.h>
#include <algorithm>
#include <Adafruit_SSD1306.h>

#define THRESHOLD 525
#define SEPERATION 7
#define HISTORY_LEN 1000


class Position {
    //int history [HISTORY_LEN];
    int last_state;
    int current_index = 0;
    //TODO NEED TO WORK ON HISTORY FOR DERIVATIVE

    /*void addToHistory(int x) {
        if (current_index >= HISTORY_LEN){
            current_index = 0;
            
        } else {
            current_index++;
        }

        history[current_index] = x;
    }*/

    public:
        int left_sens;
        int right_sens;
        int x;
        int no_change = 0; //Stores how long there has been no change for
        bool r, l;
        int rr, rl;
        int last;
        
    
        Position(int left_sensor, int right_sensor) {
            right_sens = right_sensor;
            left_sens = left_sensor;
        };

        Position() {};

        void setSensors(int left_sensor, int right_sensor) {
            right_sens = right_sensor;
            left_sens = left_sensor;
        }

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
                    x = 100;  //TODO Always turn left?
                }
            }
            if (x == last) {
                no_change++; //used for derivative so when the value changes we get a sharp spike then
            } else {         //it inversely decays
                no_change = 0;
                last_state = last;
            }
            //addToHistory(x);
            last = x;
           return x;
        }
        void showLR(Adafruit_SSD1306 display) {
            display.println(rr);
            display.println(rl);
        }

        int getXValue() {
            return read();
        }

        int getDerivative() {
            return ((x - last_state) * 2) / no_change;
        }
};
        
