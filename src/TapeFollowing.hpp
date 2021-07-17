#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "Position.hpp"
#include "Steering.hpp"

class TapeFollowing {
    int d, p, i, x, g, error;
    int kp, ki, kd;
    int lasterr;
    Position pos;
    Steering Wheels;

    public:
        TapeFollowing(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev, int left_sensor, int right_sensor);

        void followTape();

        void showValues(Adafruit_SSD1306 display);

        void stop();
};