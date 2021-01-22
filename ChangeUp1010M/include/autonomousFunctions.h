#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
double offset = 15.4;
using namespace vex;

void lockWheels() {
  LeftMotorB.stop(brakeType::hold);
  LeftMotorF.stop(brakeType::hold);
  RightMotorF.stop(brakeType::hold);
  RightMotorB.stop(brakeType::hold);
}

int matchTimer() {
  // 128x64
  bool matchOver = false;
  int timeRemaining = 105;
  int minutesLeft = timeRemaining / 60;
  int secondsLeft = timeRemaining % 60;

  while (!matchOver) {

    Controller1.Screen.setCursor(6, 0);
    Controller1.Screen.clearLine(4);
    minutesLeft = timeRemaining / 60;
    secondsLeft = timeRemaining % 60;
    Controller1.Screen.print("Match Time: ");
    Controller1.Screen.print(minutesLeft);
    Controller1.Screen.print(":");
    Controller1.Screen.print(secondsLeft);
    vex::task::sleep(1000);
    timeRemaining--;
    switch (timeRemaining) {
    case 60:
      Controller1.rumble("-");
      Controller1.Screen.setCursor(6, 0);
      Controller1.Screen.print("60 Seconds Remain");
      break;
    case 30:
      Controller1.rumble("--");
      break;
    case 15:
      Controller1.rumble("..");
      break;
    case 5:
      Controller1.rumble(".");
      break;
    case 4:
      Controller1.rumble(".");
      break;
    case 3:
      Controller1.rumble(".");
      break;
    case 2:
      Controller1.rumble(".");
      break;
    case 1:
      Controller1.rumble(".");
      break;
    default:
      break;
    }
  }
  return 0;
}



int speedometer() {
  Brain.Screen.setFont(propM);

  while (true) {
    Brain.Screen.printAt(0, 40, "Elevator 1 RPM: %f", Elevator.velocity(rpm));
    Brain.Screen.printAt(0, 60, "Elevator 2 RPM: %f", Elevator2.velocity(rpm));
    Brain.Screen.printAt(0,80,"Inertial Sensor Heading: %f", Inertial17.rotation(deg)-14.8);
    task::sleep(200);
  }
  return 0;
}

int rotateImages() {
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.drawImageFromFile("linus.png", 0, 0);
    task::sleep(5000);
    Brain.Screen.drawImageFromFile("1010.png", 0, 0);
    task::sleep(5000);
  }
  return 0;
}

void driveForward(int speed, int rot,
                  int time) { // Drive forward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);
  vex::task::sleep(time);
}
void driveForwarIntake(int speed, int rot, int time) { // Drive forward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct); 
  
  vex::task::sleep(time);
}
void driveBackward(
    int speed, int rotation,
    int time) { // Drive backward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
}

void driveRight(int speed, int rotation,
                int time) { // Turn right using motor degrees

  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
}
void intake(int time, int speed, int rotation) {
  IntakeL.setVelocity(speed, velocityUnits::pct);
  IntakeR.setVelocity(speed, velocityUnits::pct);

  IntakeL.rotateFor(rotation, rotationUnits::deg, false);
  IntakeR.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
}
void calibrateInertial() {
  Inertial17.calibrate();
  while (Inertial17.isCalibrating()) {
    wait(100, msec);
  }
}
void inertialLeft(int speed, float degreee) {
  
  LeftMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  waitUntil((Inertial17.rotation(degrees) <= (degreee - 14.8)));
  Controller1.Screen.print(Inertial17.rotation(degrees)-14.8);
  lockWheels();

  task::sleep(200);
}
void inertialRight(int speed, float degree) {
  LeftMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  waitUntil((Inertial17.rotation(degrees) >= (degree - 14.8)));
  lockWheels();
  task::sleep(200);
}
void driveLeft(int speed, int rotation,
               int time) { // Turn left using motor degrees

  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
}

void intakeScore(int time, int rotation) {
  IntakeL.setVelocity(127, pct);
  IntakeR.setVelocity(127, pct);
  Elevator.setVelocity(127, pct);
  Elevator2.setVelocity(127, pct);
  IntakeL.rotateFor(rotation, rotationUnits::deg, false);
  IntakeR.rotateFor(rotation, rotationUnits::deg, false);
  Elevator.rotateFor(rotation, rotationUnits::deg, false);
  Elevator2.rotateFor(rotation, rotationUnits::deg, false);
  task::sleep(time);
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}

void releaseBall(int speed, int rotation, int time){
      IntakeL.setVelocity(127, pct);
    IntakeR.setVelocity(127, pct);
    Elevator.setVelocity(127, pct);
    Elevator2.setVelocity(-127, pct);
  IntakeL.rotateFor(rotation, rotationUnits::deg, false);
  IntakeR.rotateFor(rotation, rotationUnits::deg, false);
  Elevator.rotateFor(-rotation, rotationUnits::deg, false);
  Elevator2.rotateFor(-rotation, rotationUnits::deg, false);
  task::sleep(time);
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void holdBall(int speed, int rotation, int time){
      IntakeL.setVelocity(127, pct);
    IntakeR.setVelocity(127, pct);
    Elevator.setVelocity(127, pct);
  IntakeL.rotateFor(rotation, rotationUnits::deg, false);
  IntakeR.rotateFor(rotation, rotationUnits::deg, false);
  Elevator.rotateFor(-rotation, rotationUnits::deg, false);
  task::sleep(time);
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}

void elevatorScoreTwo(int time, int rotation){
      Elevator.setVelocity(127, pct);
    Elevator2.setVelocity(127, pct);
  Elevator.rotateFor(rotation, rotationUnits::deg, false);
  Elevator2.rotateFor(rotation, rotationUnits::deg, false);
  task::sleep(time);
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void timeScore(int sec) {
  Elevator.spin(fwd, 100, pct);
  Elevator2.spin(fwd, 100, pct);
  task::sleep(sec);
}

void timeIntake(int sec) {
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  vex::task::sleep(sec);                                               
}
void timeOuttake(int sec){
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  Elevator.spin(reverse, 100, pct);
  Elevator2.spin(reverse, 100, pct);
  vex::task::sleep(sec);   
}

void resetEncoders() {
  LeftMotorF.resetPosition();
  LeftMotorB.resetPosition();
  RightMotorF.resetPosition();
  RightMotorB.resetPosition();
}