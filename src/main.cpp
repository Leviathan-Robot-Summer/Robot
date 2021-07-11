#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Position.cpp"
#include "Steering.cpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

#define RIGHT_IR PA5
#define LEFT_IR PA4
#define right_fwd PA_1
#define right_rev PA_2
#define left_fwd PA_3
#define left_rev PA_6

Steering wheels(left_fwd, left_rev, right_fwd, right_rev);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Position position(LEFT_IR, RIGHT_IR);

void reset_display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0); //test comment zach pc

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

  wheels.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  wheels.steer(0);
  reset_display();
  display.println("FWD");
  display.display();
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
}
