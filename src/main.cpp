#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "TapeFollowing.hpp"
#include "Collection.hpp"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

#define RIGHT_IR PA5
#define LEFT_IR PA4
#define right_fwd PA_6 //driving motors are on TIMER3 pins
#define right_rev PA_7
#define left_fwd PB_0
#define left_rev PB_1
#define CAN_COUNTER PB5
#define SERVO_CAN_SORTER PA0 //servos must be on TIMER2 pins

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TapeFollowing pid(left_fwd, left_rev, right_fwd, right_rev, LEFT_IR, RIGHT_IR);
Collection collection(CAN_COUNTER, SERVO_CAN_SORTER);
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
  pinMode(left_fwd, OUTPUT);
  pinMode(left_rev, OUTPUT);
  pinMode(right_fwd, OUTPUT);
  pinMode(right_rev, OUTPUT);
  pinMode(CAN_COUNTER, INPUT_PULLDOWN);
  
  
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
  for (int j = 0; j < 1000; j++) {
    pid.followTape();
    reset_display();
    pid.showValues(display);
    display.display();
    delay(10);
  }
  pid.stop();
  reset_display();
  display.println(analogRead(PA7));
  display.display();
  delay(5000);
}