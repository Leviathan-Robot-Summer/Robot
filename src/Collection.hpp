#include <Servo.h>

class Collection {
    int numberOfCans;
    int counterPin;
    int servoPin;
    Servo sortingFlap;

    public:
        // Constructor initializes numberOfCans to 0 and assigns pins for the servo
        // and microswitch.
        Collection(int CAN_COUNTER, int SERVO_CAN_SORTER);

        void begin();

        // This function is run as an interrupt from setup each time the microswitch for 
        // can-counting is pressed. It increments @numberOfCans; and moves the
        // flap once numberOfCans >= 3.
        void checkPin();

        void returnToNormal();

        int getCanAmount();

        void switchManually(int selection);
};