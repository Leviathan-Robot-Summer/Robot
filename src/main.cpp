#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "TapeFollowing.hpp"
#include "Collection.hpp"
// #include <Heartbeat.h>
#include <cstdlib>
//#include <Steering.cpp>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

#define RIGHT_IR PA5
#define LEFT_IR PA4
#define right_fwd PB_9
#define right_rev PB_8
#define left_fwd PA_9
#define left_rev PA_8
#define built_in_LED PC13 //????

#define CAN_COUNTER PB5
#define CAN_SENSOR_BACK PA7
#define CAN_SENSOR_FRONT PA6
#define SERVO_CAN_SORTER PA0 //servos must be on TIMER2 pins

#define NUM_LOOPS 100 //determines the delay of the sorting servo
#define CAN_THRESHOLD 70

Collection collection(CAN_COUNTER, SERVO_CAN_SORTER);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TapeFollowing pid(left_fwd, left_rev, right_fwd, right_rev, LEFT_IR, RIGHT_IR);
int count = 0;
bool checking = true; // we don't want the loop to detect cans while the servo is flipping.
bool canStuck = false;

//Steering wheels(left_fwd, left_rev, right_fwd, right_rev);

void reset_display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0); 
}

void collectionCounter() {
  digitalWrite(PB11, LOW);
  for (int i = 0; i < 35; i++){
    loop();
  }
  collection.checkPin();
  for (int i = 0; i < NUM_LOOPS; i++){  //in order to have the loop running while the ramp is flipping, we use the loop as a delay.
    loop();
  }
  collection.returnToNormal();
}

// should only run if front sensor detects a can but back doesn't.
// function waits a bit to see if the can is coming.
// if not, then it ...
void dislodgeCan() {
  for (int i = 0; i < 10; i++){
    loop();
  }
  if (analogRead(CAN_SENSOR_BACK) < CAN_THRESHOLD){
    canStuck = false;
    return;
  }
  else {
    //do something, maybe servo?
    digitalWrite(PB11, HIGH);
  }
}

void setup() {
  pinMode(built_in_LED, OUTPUT);
  delay(300);
  //pinMode(CAN_COUNTER, INPUT_PULLUP);
  //pinMode(CAN_SWITCH, INPUT_PULLUP);
  pinMode(PB10, OUTPUT); //testing LED to see when can is detected. Will remove later. - hs
  pinMode(PB11, OUTPUT); //testing LED to see when can is stuck. Will remove later (probably) - hs
  pinMode(CAN_SENSOR_FRONT, INPUT_ANALOG); //just take the analog output instead of the digital schmitt trigger output.
  pinMode(CAN_SENSOR_BACK, INPUT_ANALOG);
  //pinMode(left_fwd, OUTPUT);
  //pinMode(left_rev, OUTPUT);
  //pinMode(right_fwd, OUTPUT);
  //pinMode(right_rev, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  reset_display();
  display.println("Hello world!");
  display.display();
  collection.begin();
  //attachInterrupt(digitalPinToInterrupt(CAN_COUNTER), collectionCounter, RISING);
  //wheels.start();
}

void loop() {
  pid.followTape();
  delay(10);
  if (checking){
    if (analogRead(CAN_SENSOR_BACK) < CAN_THRESHOLD){
      checking = false;  
      canStuck = false;                                      
      collectionCounter();
      checking = true;
    }
    else if (analogRead(CAN_SENSOR_FRONT) < CAN_THRESHOLD){
      checking = false;
      canStuck = true;
      dislodgeCan();
      checking = true;
    }
  }
  if (count % 1000 == 0) {
    digitalWrite(built_in_LED, HIGH);
  } else if (count % 1000 == 500) {
    digitalWrite(built_in_LED, LOW);
  }
  if (count % 100 == 0) {
    reset_display();
    display.println(count / 100);
    pid.showValues(display);
    display.display();
  }
  count++;
}

