#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "TapeFollowing.hpp"
#include "Collection.hpp"
#include <thread>
#include <Heartbeat.h>
#include <cstdlib>
//#include <Steering.cpp>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

#define RIGHT_IR PA5
#define LEFT_IR PA4
#define right_fwd PA_1
#define right_rev PA_2
#define left_fwd PA_9
#define left_rev PA_8
#define built_in_LED PC13 //????

#define CAN_COUNTER PB5
#define SERVO_CAN_SORTER PA0 //servos must be on TIMER2 pins
#define CAN_SWITCH PA8

Collection collection(CAN_COUNTER, SERVO_CAN_SORTER);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TapeFollowing pid(left_fwd, left_rev, right_fwd, right_rev, LEFT_IR, RIGHT_IR);
int count = 0;


//Steering wheels(left_fwd, left_rev, right_fwd, right_rev);

void reset_display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0); 
}

void collectionCounter() {
  collection.checkPin();
  display.println(collection.getCanAmount());
  display.display();
}

void setup() {
  pinMode(built_in_LED, OUTPUT);
  delay(300);
  pinMode(CAN_COUNTER, INPUT_PULLUP);
  pinMode(CAN_SWITCH, INPUT_PULLUP);
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
  attachInterrupt(digitalPinToInterrupt(CAN_COUNTER), collectionCounter, RISING);
  //wheels.start();
}

void loop() {
  
  pid.followTape();
  delay(10);
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
