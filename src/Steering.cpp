#include <stdio.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define MOTORFREQ 1000
#define MOTOR_MAX 4096 //12 Bit max 
#define MOTOR_MIN 2500 //minimum PWM for the wheels to move the robot

#define NORMAL_PWR 10 // the normal power that the robot should move at
#define MAX_PWR_FWD 100 // the max power the robot should move forward at


/** Object that represents a motor and the allowed controls for it
 *  + power means motor spins forward
 *  - power means motor spins in reverse 
 * 
 *  @author Lukas
 */ 
class Motor {
    private:
        PinName fwd; // pin that controls fwd spin
        PinName rev; // pin that controls rev spin
        int pwm_constant = (MOTOR_MAX - MOTOR_MIN) / 100; // pwm range turned into a percentage
        int pwr = NORMAL_PWR; //initially the motor will be moving at normal power


    public:
        /** Constructs a new motor and assigns @param fwd and @param rev to fwd and rev pins respectively
         * 
         * @author Lukas
         */
        Motor(PinName fwd, PinName rev) {
            fwd = fwd;
            rev = rev;
        }

        /** Initializes a new motor with pins to be assigned later
         * 
         *  @author Lukas
         */
        Motor() {}


        /** Assigns @param fwd_pin and @param rev_pin to fwd and rev pins respectively
         * 
         * @author Lukas
         */
        void set_pins(PinName fwd_pin, PinName rev_pin) {
            fwd = fwd_pin;
            rev = rev_pin;
        }

        /** Sets the motor power from -100 to 100 where - numbers set reverse power and + set forward
         * 
         * @author Lukas
         */ 
        void power(int power) { //+ is forward and - is reverse in range [-100, 100]
            if (power > 100) {power = 100;}
            if (power < -100) {power = -100;}
            stop();
           // delay(5);
            if (power > 0) {
                pwm_start(fwd, MOTORFREQ, MOTOR_MIN + power * pwm_constant, RESOLUTION_12B_COMPARE_FORMAT);
            } else if (power < 0) {
                pwm_start(rev, MOTORFREQ, MOTOR_MIN - power * pwm_constant, RESOLUTION_12B_COMPARE_FORMAT);
            }
            pwr = power;
        }


        /** Stops the motor
         *  
         *  @author Lukas
         */ 
        void stop() {
            pwm_start(fwd, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
            pwm_start(rev, MOTORFREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
        }


        /** Returns the current power of the motor
         * 
         * @author Lukas
         */
        int getPower() {
            return pwr;
        }
};


/** Abstraction of steering 2 wheels in a driving chassis
 * 
 * @author Lukas
 */ 
class Steering {
    Motor left;
    Motor right;
 
    public:
        /** Constructs a new steering object
         * @param left_fwd: pin for the left forward wheel input
         * @param left_rev: pin for the left reverse wheel input
         * @param right_fwd: pin for the right forward wheel input
         * @param right_rev: pin for the right reverse wheel input
         * 
         * @author Lukas
         */ 
        Steering(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
            left.set_pins(left_fwd, left_rev);
            right.set_pins(right_fwd, right_rev);
        };


        /** Initializes a new steering object
         * 
         * @author Lukas
         */ 
        Steering() {}


        /** Assigns all pins to a new steering object
         * @param left_fwd: pin for the left forward wheel input
         * @param left_rev: pin for the left reverse wheel input
         * @param right_fwd: pin for the right forward wheel input
         * @param right_rev: pin for the right reverse wheel input
         * 
         * @author Lukas
         */ 
        void setPins(PinName left_fwd, PinName left_rev, PinName right_fwd, PinName right_rev) {
            left.set_pins(left_fwd, left_rev);
            right.set_pins(right_fwd, right_rev);
            //left(left_fwd, left_rev);
            //left = &left_mot;
            //right(right_fwd, right_rev);
            //right = &right_mot;
        };


        /** Starts both wheels at NORMAL_PWR going fwd
         * 
         * @author Lukas
         */ 
        void start() {
            left.power(NORMAL_PWR);
            right.power(NORMAL_PWR);
        }


        /** Steers the car
         * @param amount: how much the car is steered in range [-100, 100] - to the left + to the right
         * 
         * @author Lukas
         */
        void steer(int amount) {
            right.power(NORMAL_PWR + amount);
            left.power(NORMAL_PWR - amount);  
        }


        /** Incramentally increases the speed of the wheels
         * @returns true if the speed changed and false otherwise
         * 
         * @author Lukas
         */
        bool increaseFwdSpeed() {
            bool increased = false;
            if (right.getPower() == left.getPower()) {
                if (left.getPower() < MAX_PWR_FWD) {
                    left.power(1 + left.getPower());
                    right.power(1 + right.getPower());
                }
                increased = true;
            }
            return increased;
        }           
        
        /** Gets the direction of the wheels
         * @returns the difference of the 2 wheel powers left - right
         * 
         * @author
         */ 
        int direction() {
            return left.getPower() - right.getPower();
        }

        /** Stops both wheels
         * 
         * @author Lukas
         */ 
        void stop() {
            left.stop();
            right.stop();
        }


        /** Shows the power of the left and right wheel
         * @param display: the display these values are printed to
         * 
         * @author Lukas
         */ 
        void showPower(Adafruit_SSD1306 display) {
            display.println(left.getPower());
            display.println(right.getPower());
        }
};