#include <Servo.h>

class Collection {
    int numberOfCans;
    int servoPin;
    int dislodgerPin;
    int dumperPin;
    int vPin;
    Servo sortingFlap;
    Servo dislodger;
    Servo dumper;
    Servo V;

    public:
        // Constructor initializes numberOfCans to 0 and assigns pins for the servo
        // and microswitch.
        Collection(int SERVO_CAN_SORTER, int DISLODGER, int DUMPER, int V);

        void begin();

        // This function is run as an interrupt from setup each time the microswitch for 
        // can-counting is pressed. It increments @numberOfCans; and moves the
        // flap once numberOfCans >= 3.
        void checkPin();

        void returnToNormal();

        void dislodge();

        void lodge();

        void dump();

        void retractV();

        void detachV();

        int getCanAmount();

        void switchManually(int selection);
};