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

#define CAN_SENSOR_BACK PA7
#define CAN_SENSOR_FRONT PA6
#define SERVO_CAN_SORTER PA0 //servos must be on TIMER2 pins
#define DISLODGER PA1
#define DUMPER PA2
#define V PA3
#define BOX_DETECTOR PB4

#define SORTING_DELAY 1000 //determines the delay of the sorting servo
#define CAN_THRESHOLD 70
#define DISLODGE_DELAY 50
#define STUCK_DELAY 100
#define V_DELAY 40000 //amount of time after initial startup until V retracts. In milliseconds.

Collection collection(SERVO_CAN_SORTER, DISLODGER, DUMPER, V);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TapeFollowing pid(left_fwd, left_rev, right_fwd, right_rev, LEFT_IR, RIGHT_IR);
int count = 0;
bool checking = true; // we don't want the loop to detect cans while the servo is flipping.
bool canStuck = false;
bool running = true;
unsigned long init_time;
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
  for (int i = 0; i < SORTING_DELAY; i++){  //in order to have the loop running while the ramp is flipping, we use the loop as a delay.
    loop();
  }
  collection.returnToNormal();
}

// should only run if front sensor detects a can but back doesn't.
// function waits a bit to see if the can is coming.
// if not, then it ...
void dislodgeCan() {
  for (int i = 0; i < STUCK_DELAY; i++){ //wait a bit to see if the can naturally gets unstuck
    loop();
  }
  if (analogRead(CAN_SENSOR_BACK) < CAN_THRESHOLD){ 
    canStuck = false;
  }
  else {
    collection.dislodge();
    digitalWrite(PB11, HIGH);
    for (int i = 0 ; i < DISLODGE_DELAY; i++){
      loop();
    }
    collection.lodge();
  }
}


// stops tape following, dumps, then stops for 30 seconds.
void dump() {
  digitalWrite(PB10, HIGH);
  running = false;
  pid.stop();
  delay(1000);
  collection.dump();
  reset_display();
  display.println("Done :) !");
  display.display();
  //delay(30000);
  //running = false;
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
  pinMode(BOX_DETECTOR, INPUT_PULLDOWN);
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
  digitalWrite(PB10, LOW);
  attachInterrupt(digitalPinToInterrupt(BOX_DETECTOR), dump, FALLING);
  init_time = millis();
  //attachInterrupt(digitalPinToInterrupt(CAN_COUNTER), collectionCounter, RISING);
  //wheels.start();
}

void loop() {
  if (!running) {
    pid.stop();
    return;
  }
  pid.followTape();
  delay(1);
  if (checking){
    if (analogRead(CAN_SENSOR_BACK) < CAN_THRESHOLD){ // can is in the correct position.
      checking = false;  
      canStuck = false;                                      
      collectionCounter();
      checking = true;
    }
    else if (analogRead(CAN_SENSOR_FRONT) < CAN_THRESHOLD) { // can is possibly stuck.
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
  if (millis() - init_time > V_DELAY) collection.retractV();
  count++;
}

