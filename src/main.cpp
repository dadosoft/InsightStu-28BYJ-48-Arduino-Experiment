/* 28BYJ-48 Speed and Reverse controller | v1.2 | by Stu */

#include <Arduino.h> /* Include Arduino GLibs */
#include <Stepper.h> /* Include Stepper config */

const int reverser = 3;
const int onOffSwitch = 2;
const int shaftRevs = 32;
const int gearRed = 64;
const int stepsPerRev = 200; /* (shaftRevs * gearRed) is currently broken... */

int stepCount = 0;

Stepper myStepper(stepsPerRev, 8, 10, 9, 11); /* Pin 9 and 10 are reversed to make Stepper.h work with 28BYJ-48 */ 


void setup() {
  pinMode(reverser, INPUT);
  pinMode(onOffSwitch, INPUT);
}

void loop() {
  
  int sensorReading = analogRead(A0);
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  int reverse = digitalRead(reverser);

  if (motorSpeed > 0 && reverse == HIGH) {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(stepsPerRev / 100);
  }
  else if (motorSpeed > 0 && reverse == LOW) {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(-stepsPerRev / 100);
    }
}

void toggle(){
  
}
