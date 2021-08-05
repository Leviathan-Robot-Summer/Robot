#define RIGHT_IR PA5
#define LEFT_IR PA4
#define right_fwd PB_9
#define right_rev PB_8
#define left_fwd PA_9
#define left_rev PA_8
#define built_in_LED PB2 //????

#define CAN_SENSOR_BACK PA6
#define CAN_SENSOR_FRONT PA7
#define SERVO_CAN_SORTERPIN PA1 //servos must be on TIMER2 pins
#define DISLODGERPIN PA0 //not used??
#define DUMPERPIN PA2
#define VPIN PA3
#define BOX_DETECTOR PB5

#define NUMBER_OF_CHECKS_DUMP 10
#define SKYCRANE_BRAKE PA_10
#define SKYCRANE_DISTANCE_PING PB12
#define SKYCRANE_DISTANCE_ECHO PB13

//servo angles -- needs calibration
#define DEFAULT_LEVEL 97
#define UPPER_LEVEL 168
#define LOWER_LEVEL 121 //35 degrees more than UPPER_LEVEL

#define DISLODGE_DEFAULT 0
#define DISLODGE_KICK 45

#define DUMPER_DEFAULT 130
#define DUMPER_RELEASED 0

#define V_DEFAULT 15
#define V_RETRACTED 160