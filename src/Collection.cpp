#include <Arduino.h>
#include <Servo.h>

#define LOWER_ANGLE 10
#define HIGHER_ANGLE 40

class Collection {
    int numberOfCans;
    int counterPin;
    int servoPin;
    Servo sortingFlap;

    public:
        // Constructor initializes numberOfCans to 0 and assigns pins for the servo
        // and microswitch.
        Collection(int CAN_COUNTER, int SERVO_CAN_SORTER) {
            numberOfCans = 0;
            counterPin = CAN_COUNTER;
            servoPin = SERVO_CAN_SORTER;
        }

        void begin() {
            sortingFlap.attach(servoPin);
            sortingFlap.write(15);
        }

        // This function is run as an interrupt from setup each time the microswitch for 
        // can-counting is pressed. It increments @numberOfCans; and moves the
        // flap once numberOfCans >= 3.
        void checkPin() {
            numberOfCans++;
            if (numberOfCans >= 3) {
                sortingFlap.write(45);
            }
        }

        int getCanAmount() {
            return numberOfCans;
        }
};