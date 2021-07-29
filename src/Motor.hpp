#include <Arduino.h>

class Motor {
    private:
        PinName fwd;
        PinName rev;
        int pwm_constant; // MAX pwm divided by percentage
        int pwr;

    public:
        Motor(PinName fwd, PinName rev);
        Motor();

        void set_pins(PinName fwd_pin, PinName rev_pin);

        void power(int power);  //+ is forward and - is reverse in range [-100, 100]
            
        void stop();

        int getPower();
};
