#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
<<<<<<< HEAD
#include "TapeFollowing.hpp"

=======
#include <Servo.h>
#include "Position.cpp"
#include "Steering.cpp"
#include "Collection.cpp"
>>>>>>> a9aefca3a74952f0fa74e1cd67023fa790f0aba1

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
<<<<<<< HEAD
TapeFollowing pid(left_fwd, left_rev, right_fwd, right_rev, LEFT_IR, RIGHT_IR);
//Steering wheels(left_fwd, left_rev, right_fwd, right_rev);
=======
Position position(LEFT_IR, RIGHT_IR);
Collection collection(CAN_COUNTER, SERVO_CAN_SORTER);
>>>>>>> a9aefca3a74952f0fa74e1cd67023fa790f0aba1

void reset_display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
<<<<<<< HEAD
  display.setCursor(0,0); 
=======
  display.setCursor(0,0); //test comment zach pc
}

void collectionCounter() {
  collection.checkPin();
  display.println(collection.getCanAmount());
  display.display();
>>>>>>> a9aefca3a74952f0fa74e1cd67023fa790f0aba1
}

void setup() {
  pinMode(left_fwd, OUTPUT);
  pinMode(left_rev, OUTPUT);
  pinMode(right_fwd, OUTPUT);
  pinMode(right_rev, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  reset_display();
  display.println("Hello world!");
  display.display();
  //wheels.start();
}

<<<<<<< HEAD
void loop() {
  for (int j = 0; j < 1000; j++) {
    pid.followTape();
    reset_display();
    pid.showValues(display);
    display.display();
    delay(10);
  }
  pid.stop();
=======
  wheels.start();
  // for (int i = 50; i < 300; i = i + 50) {
  //   wheels.steer(i);
  //   reset_display();
  //   display.println(i);
  //   display.display();
  //   delay(2000);
  // }

  pinMode(CAN_COUNTER, INPUT_PULLDOWN);
  collection.begin();
  attachInterrupt(digitalPinToInterrupt(CAN_COUNTER), collectionCounter, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  wheels.steer(0);
>>>>>>> a9aefca3a74952f0fa74e1cd67023fa790f0aba1
  reset_display();
  display.println(analogRead(PA7));
  display.display();
<<<<<<< HEAD
  delay(5000);
=======
  delay(2000);

  wheels.steer(100);
  reset_display();
  display.println("RIGHT");
  display.display();
  delay(2000);

  wheels.steer(-100);
  reset_display();
  display.println("LEFT");
  display.display();
  delay(2000);


  /*reset_display();
  display.println(analogRead(RIGHT_IR));
  display.println(analogRead(LEFT_IR));
  display.println(position.getXValue());
  display.println(position.getDerivative());
  display.display();*/
>>>>>>> a9aefca3a74952f0fa74e1cd67023fa790f0aba1
}
