/* 28BYJ-48 Speed and Reverse controller | v0.2 | by Stu */

#include <Arduino.h> /* Include Arduino GLibs */
#include <Stepper.h> /* Include Stepper config */
#include <IRremote.h> /* Include IT libs */

const int onOffSwitch = 2;  /* Toggle Switch Pin */
const int reverser = 3;   	/* Reverse Button Pin */
const int shaftRevs = 32;
const int gearRed = 64;
const int stepsPerRev = 200; /* (shaftRevs * gearRed) is currently broken... */

int stepCount = 0;
int bState = HIGH; 
int bPrev = LOW;
int bCurr;

unsigned long time = 0;
unsigned long debounce = 200UL;

Stepper myStepper(stepsPerRev, 8, 10, 9, 11); /* Pin 9 and 10 are reversed to make Stepper.h work with 28BYJ-48 */ 


void setup() {
  pinMode(reverser, INPUT);
  pinMode(onOffSwitch, INPUT);
}

void loop() {
  int sensorReading = analogRead(A0);
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  int reverse;

  bCurr = digitalRead(reverser);
  if (bCurr == HIGH && bPrev == LOW && millis() - time > debounce){
    if (bState == HIGH){
      reverse = LOW;
    }
    else{
      reverse = HIGH;
    }
    time = millis();
  } 
  
  if (motorSpeed > 0 && reverse == LOW) {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(stepsPerRev / 100);
  }
  else if (motorSpeed > 0 && reverse == HIGH) {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(-stepsPerRev / 100);
    }
}
