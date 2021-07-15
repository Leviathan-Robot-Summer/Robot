#include <stdio.h>
#include <Arduino.h>
#include <algorithm>
#include <Adafruit_SSD1306.h>

#define THRESHOLD 550
#define SEPERATION 7
#define HISTORY_LEN 1000


class Position {
    int history [HISTORY_LEN];
    int current_index = 0;
    //TODO NEED TO WORK ON HISTORY FOR DERIVATIVE

    void addToHistory(int x) {
        if (current_index >= HISTORY_LEN){
            current_index = 0;
            
        } else {
            current_index++;
        }

        history[current_index] = x;
    }

    public:
        int left_sens;
        int right_sens;
        int x;
        int no_change = 0; //Stores how long there has been no change for
        bool r;
        bool l;
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
            r = analogRead(right_sens) > THRESHOLD;
            l = analogRead(left_sens) > THRESHOLD;
            if (r && l) {
                x = 0;
            } else if (r) {
                x = 1;
            } else if (l) {
                x = -1;
            } else {
                if (last > 0) {
                    x = SEPERATION;
                } else if (last < 0) {
                    x = -SEPERATION;
                } else {
                    x = 100;  //TODO Always turn left?
                }
            }
            if (x == history[current_index]) {
                no_change++; //used for derivative so when the value changes we get a sharp spike then
            } else {         //it inversely decays
                no_change = 0; 
            }
            addToHistory(x);
            last = x;
            return x;
        }
        void showLR(Adafruit_SSD1306 display) {
            display.println(r);
            display.println(l);
        }

        int getXValue() {
            return read();
        }

        int getDerivative() {
            if (current_index < no_change + 1) {   
                return (x - history[HISTORY_LEN + current_index - no_change - 1]) * 10 / no_change;
            } else {
                return (x - history[current_index - no_change - 1]) * 10/ no_change;
            }  

        }
};
        
