#include "ballSorter.h"
#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Swap rightmotor B back to 3
//leftmotorb back to 4
//Elevator 2 back to 19
//Vision 19

double offset = 15.4;
int JOYSTICK_DEADZONE = 5;
int ktarget = 0;
bool intakeBool = false;
bool seenBallRed = false;
int scoreOne = 1000;
int scoreTopTime = 900;
int turntarget = 0;
int intakeSpeed = 100;
bool resetDriveEncoders = false;
void sortBall(int n1, int n2);
using namespace vex;
void resetTarget() {
  ktarget = 0;
  turntarget = 0;
}
void lockWheels() {
  LeftMotorB.stop(brakeType::coast);
  LeftMotorF.stop(brakeType::coast);
  RightMotorF.stop(brakeType::coast);
  RightMotorB.stop(brakeType::coast);
}
void brakeWheels() {
  LeftMotorB.stop(brakeType::hold);
  LeftMotorF.stop(brakeType::hold);
  RightMotorF.stop(brakeType::hold);
  RightMotorB.stop(brakeType::hold);
}
void cubeDrive() {
  float left_percent = Controller1.Axis3.value();
  float right_percent = Controller1.Axis1.value();
  LeftMotorF.spin(fwd, left_percent + right_percent, vex::velocityUnits::pct);
  LeftMotorB.spin(fwd, left_percent + right_percent, vex::velocityUnits::pct);
  RightMotorF.spin(fwd, left_percent - right_percent, vex::velocityUnits::pct);
  RightMotorB.spin(fwd, left_percent - right_percent, vex::velocityUnits::pct);
}
void expoDriveLeft(vex::directionType type, int percentage) {
  if (percentage >= 0) {
    percentage = 1.2 * pow(1.035, percentage) - 1.2 + 0.3 * percentage;
  } else {
    percentage = -percentage;
    percentage = 1.2 * pow(1.035, percentage) - 1.2 + 0.3 * percentage;
    percentage = -percentage;
  }
  LeftMotorF.spin(fwd, percentage, vex::velocityUnits::pct);
  LeftMotorB.spin(fwd, percentage, vex::velocityUnits::pct);
}
void expoDriveRight(vex::directionType type, int percentage) {
  if (percentage >= 0) {
    percentage = 1.2 * pow(1.035, percentage) - 1.2 + 0.3 * percentage;
  } else {
    percentage = -percentage;
    percentage = 1.2 * pow(1.035, percentage) - 1.2 + 0.3 * percentage;
    percentage = -percentage;
  }
  RightMotorF.spin(fwd, percentage, vex::velocityUnits::pct);
  RightMotorB.spin(fwd, percentage, vex::velocityUnits::pct);
}
void linearDrive() {
  int deadband = 5;
  // Get the velocity percentage of the left motor. (Axis3 + Axis1)
  int leftMotorSpeed =
      Controller1.Axis3.position() + Controller1.Axis1.position();
  // Get the velocity percentage of the right motor. (Axis3 - Axis1)
  int rightMotorSpeed =
      Controller1.Axis3.position() - Controller1.Axis1.position();

  // Set the speed of the left motor. If the value is less than the deadband,
  // set it to zero.
  if (abs(leftMotorSpeed) < deadband) {
    // Set the speed to zero.
    LeftMotorF.setVelocity(0, percent);
    LeftMotorB.setVelocity(0, percent);
  } else {
    // Set the speed to leftMotorSpeed
    LeftMotorF.setVelocity(leftMotorSpeed, percent);
    LeftMotorB.setVelocity(leftMotorSpeed, percent);
  }

  // Set the speed of the right motor. If the value is less than the deadband,
  // set it to zero.
  if (abs(rightMotorSpeed) < deadband) {
    // Set the speed to zero
    RightMotorF.setVelocity(0, percent);
    RightMotorB.setVelocity(0, percent);
  } else {
    // Set the speed to rightMotorSpeed
    RightMotorF.setVelocity(rightMotorSpeed, percent);
    RightMotorB.setVelocity(rightMotorSpeed, percent);
  }

  // Spin both motors in the forward direction.
  LeftMotorF.spin(forward);
  RightMotorF.spin(forward);
  LeftMotorB.spin(forward);
  RightMotorB.spin(forward);
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
        Brain.Screen.printAt(0, 80, "Left Motor F RPM: %f", LeftMotorF.velocity(rpm));
    Brain.Screen.printAt(0, 100, "Left Motor B %f", LeftMotorB.velocity(rpm));
            Brain.Screen.printAt(0, 120, "Right Motor F RPM: %f", RightMotorF.velocity(rpm));
    Brain.Screen.printAt(0, 140, "Right Motor B %f", RightMotorB.velocity(rpm));
    Controller1.Screen.print("Inertial %f", Inertial17.heading(deg));
    Controller1.Screen.clearLine();
    task::sleep(500);
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
                  int time) { // Drive forward function that uses motor revrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);

  // Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);

  vex::task::sleep(time);
  lockWheels();
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void driveForwardDrop(
    int speed, int rot,
    int time) { // Drive forward function that uses motor revrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);
  Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  Elevator2.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);

  // Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);

  vex::task::sleep(time);
  lockWheels();
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}

void driveForwardIntake(
    int speed, int rot,
    int time) { // Drive forward function that uses motor revrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);
  IntakeR.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);

  // Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);

  vex::task::sleep(time);
  lockWheels();
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void driveBackward(int speed, int rotation,
                   int time) { // Drive backward function that uses motor
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
void driveBackwardOuttake(int speed, int rotation,
                          int time) { // Drive backward function that uses motor
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);

  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  Elevator2.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  Elevator.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);

  vex::task::sleep(time);
}
void driveBackwardOuttakeNoRoll(
    int speed, int rotation,
    int time) { // Drive backward function that uses motor
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);

  IntakeR.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);

  vex::task::sleep(time);
}

void driveBackwardIntakeNoRoll(
    int speed, int rotation,
    int time) { // Drive backward function that uses motor
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);

  IntakeR.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);

  vex::task::sleep(time);
}
void driveRight(int speed, int rotation,
                int time) { // Turn right using motor revrees

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
void intake(int speed, int rotation, int time) {
  IntakeL.setVelocity(speed, velocityUnits::pct);
  IntakeR.setVelocity(speed, velocityUnits::pct);

  IntakeL.rotateFor(rotation, rotationUnits::deg, false);
  IntakeR.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
}
void calibrateInertial() {
  Inertial17.calibrate(); // Calibrate the inertials
  task::sleep(5000);
}
void inertialLeft(int speed, float degree) { // Function for turning left
  // While the reading on the inertial is less than the degree
  // Turn left using the motors
  LeftMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  waitUntil((Inertial17.heading(degrees) <= degree));
  brakeWheels(); // Hold the motors in place
  task::sleep(200);
}
void inertialRight(int speed, float revree) { // Function for turning right
  // While the reading on the inertial is less than the degree
  LeftMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  // wait until the motors are turned to the amount
  waitUntil((Inertial17.heading(degrees) >= (revree - 14.8)));
  brakeWheels();
  task::sleep(200);
}
void driveLeft(int speed, int rotation,
               int time) { // Turn left using motor revrees

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

void releaseBall(int speed, int rotation, int time) {
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
void holdBall(int speed, int rotation, int time) {
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

void elevatorScoreTwo(int rotation, int time) {
  Elevator.setVelocity(70, pct);
  Elevator2.setVelocity(70, pct);
  Elevator.rotateFor(-rotation, rotationUnits::deg, false);
  Elevator2.rotateFor(-rotation, rotationUnits::deg, false);
  task::sleep(time);
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void timeScore(int sec) {
  Elevator.spin(fwd, 100, pct);
  task::sleep(sec);
}
void scoreTop(int rotation, int time) {
  Elevator.setVelocity(85, pct);
  Elevator.rotateFor(-rotation, rotationUnits::deg, false);
  task::sleep(time);
}
void timeIntake(int sec) {
  IntakeR.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  vex::task::sleep(sec);
}
void timeOuttake(int sec) {
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  vex::task::sleep(sec);
  stopAll();
}
void driveForwardDropBall(int speed, int rotation, int time) {
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  Elevator.setVelocity(speed, velocityUnits::pct);
  Elevator2.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
  Elevator.rotateFor(rotation, rotationUnits::rev, false);
  Elevator2.rotateFor(-rotation, rotationUnits::rev, false);
  IntakeR.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  task::sleep(time);
}
void resetEncoders() {
  LeftMotorF.resetPosition();
  LeftMotorB.resetPosition();
  RightMotorF.resetPosition();
  RightMotorB.resetPosition();
}

int pidLoop() {
  while (true) {
    if (resetDriveEncoders) {
      resetDriveEncoders = false;
      intakeBool = false;
      resetEncoders();
    }

    int target = ktarget;
    int previousError = 0;
    int totalError = 0;
    int ttarget = turntarget;
    int tpreviousError = 0;
    int ttotalError = 0;
    int kintakespeed = intakeSpeed;
    /*
    Tune kP until steady minor oscillation
    Tune kD increase until oscillation doesn't exist
    Tune kI to increase position
    */
    double kP = 0.2;
    double kI = 0;   // minor change
    double kD = 0.1; // speed changes
    double tkP = 0.13;
    double tkI = 0;
    double tkD = 0.01;
    int encoderAverage =
        (LeftMotorF.position(deg) + RightMotorF.position(deg)) / 2;
    int error = target - encoderAverage;
    int derivative = error - previousError;
    double LateralmotorPower = (error * kP + totalError * kI + derivative * kD);
    int turnDifference = LeftMotorF.position(deg) - RightMotorF.position(deg);
    int terror = ttarget - turnDifference;
    int tderivative = terror - tpreviousError;
    double turnMotorPower =
        (terror * tkP + ttotalError * tkI + tderivative * tkD);
    if (intakeBool == true) {
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower,
                      voltageUnits::volt);
      LeftMotorB.spin(directionType::fwd, LateralmotorPower + turnMotorPower,
                      voltageUnits::volt);
      RightMotorF.spin(directionType::fwd, LateralmotorPower - turnMotorPower,
                       voltageUnits::volt);
      RightMotorB.spin(directionType::fwd, LateralmotorPower - turnMotorPower,
                       voltageUnits::volt);
      if (LateralmotorPower < 1.0 || turnMotorPower < 1.0) {
        Elevator.stop(hold);
        Elevator2.stop(hold);
        IntakeL.stop(vex::brakeType::coast);
        IntakeR.stop(coast);
      }
      IntakeL.spin(forward, 100, pct);
      IntakeR.spin(forward, 100, pct);
      Elevator.spin(forward, kintakespeed, pct);
      Elevator2.spin(forward, kintakespeed, pct);
    } else if (intakeBool == false) {
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower,
                      voltageUnits::volt);
      LeftMotorB.spin(directionType::fwd, LateralmotorPower + turnMotorPower,
                      voltageUnits::volt);
      RightMotorF.spin(directionType::fwd, LateralmotorPower - turnMotorPower,
                       voltageUnits::volt);
      RightMotorB.spin(directionType::fwd, LateralmotorPower - turnMotorPower,
                       voltageUnits::volt);
      Elevator.stop(hold);
      Elevator2.stop(brakeType::hold);
      IntakeL.stop(vex::brakeType::coast);
      IntakeR.stop(coast);
    }
    previousError = error;
    tpreviousError = terror;
    task::sleep(20);
  }
  return 1;
}
double convertDistance(double distance) { return distance * 11.1; }
void locateBallRed() {
  seenBallRed = false;
  while (seenBallRed == false) {
    Vision19.takeSnapshot(Vision19__REDBALL);
    if (Vision19.objectCount > 0) {
      seenBallRed = true;
      break;
    }
    IntakeL.spin(fwd, 100, pct);
    IntakeR.spin(fwd, 100, pct);
    Elevator2.stop();
  }
  IntakeL.stop();
  IntakeR.stop();
}
void locateBallBlue() {
  seenBallRed = false;
  while (seenBallRed == false) {
    Vision19.takeSnapshot(Vision19__BLUEBALL);
    if (Vision19.objectCount > 0) {
      seenBallRed = true;
      break;
    }
    IntakeL.spin(fwd, 100, pct);
    IntakeR.spin(fwd, 100, pct);
    Elevator2.stop();
  }
  IntakeL.stop();
  IntakeR.stop();
}

/*
The variables scoreOne and scoreTopTime can be edited at the very top of this
header file
*/
void shuffleSortRed() { // This is for red side autos
  // Start sequence when lined up at the goal with 1 ball in vision position
  timeIntake(200);
  stopAll();
  scoreTop(scoreOne, scoreTopTime);
  int ballUp = 1000;
  elevatorScoreTwo(
      ballUp,
      720); // Preset for bringing the ball up to the top but not scoring
  locateBallRed();
  stopAll();
  scoreTop(scoreOne, scoreTopTime);
  locateBallRed();
  stopAll();
  elevatorScoreTwo(ballUp, 720);
  locateBallBlue();
  stopAll();
  scoreTop(scoreOne, scoreTopTime);
  stopAll();
}
void shuffleSortBlue() { // This is for blue side autos
  // Start sequence when lined up at the goal with 1 ball in vision positionf

  scoreTop(scoreOne, scoreTopTime);
  int ballUp = 880;
  elevatorScoreTwo(
      ballUp,
      720); // Preset for bringing the ball up to the top but not scoring
  locateBallBlue();
  scoreTop(scoreOne, scoreTopTime);
  locateBallBlue();
  elevatorScoreTwo(ballUp, 720);
  locateBallRed();
  scoreTop(scoreOne, scoreTopTime);
  stopAll();
  driveBackward(75, convertDistance(60), 1500);
}

void redAutoShuffle() { // Only shuffle sorting first goal
  driveForward(65, convertDistance(75), 1300); // Speed,Distance (motor degrees), Time Allocated
  Inertial17.setHeading(20,deg);
  inertialRight(75, Inertial17.heading() + 136); // Speed, Heading Position
  driveForwardIntake(60, convertDistance(70), 900);
  stopAll();
  shuffleSortRed();
  stopAll();
  driveBackwardOuttake(75, convertDistance(70), 1000);
  Inertial17.setHeading(20, deg);
  inertialRight(75, 163);
  driveForwardDropBall(70, convertDistance(90), 1200);
  inertialLeft(75, Inertial17.heading() - 75);


  //change the stuff below this 
  driveForwardIntake(100, convertDistance(53), 800); 
  stopAll();
  timeIntake(100);
  locateBallRed();
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(2000, rotationUnits::deg, false);
  Elevator2.rotateFor(2000, rotationUnits::deg, false);
  task::sleep(20000);//score indefinetly until time ends
}

void redAutoShuffleOpposite() { // Only shuffle sorting first goal
  driveForward(65, convertDistance(75),
               1300);     // Speed,Distance (motor degrees), Time Allocated
  inertialRight(75, 229); // Speed, Heading Position
  driveForwardIntake(75, convertDistance(70), 1000);
  shuffleSortRed();
  stopAll();
}
void redAuton() {
  int scoreOne = 1000;
  int scoreTopTime = 900;
  driveForward(75, convertDistance(70), 1300);
  inertialRight(75, 126);
  driveForwardIntake(75, convertDistance(70), 1000);
  stopAll();
  scoreTop(scoreOne, scoreTopTime);
  timeOuttake(100);
  driveBackward(75, convertDistance(70), 1500);
  inertialRight(75, 270);
  driveForward(100, convertDistance(125), 1400);
  inertialLeft(75, Inertial17.heading() - 89);
  driveForward(75, convertDistance(49), 600);
  elevatorScore(800, 5);
  stopAll();
  timeOuttake(100);
  stopAll();
  driveBackward(75, convertDistance(40), 500);
  inertialRight(75, Inertial17.heading() + 90);
  driveForwardDrop(80, convertDistance(133), 1800);
  inertialLeft(75, Inertial17.heading() - 55);
  driveForwardIntake(75, convertDistance(85), 800);
  sortBall(3, 1);
  stopAll();
  driveBackward(75, 400, 10000000);
}

void redAutoSecondGoal() { // This auto goes up to sorting the 2nd goal
  int scoreOne = 1000;
  int scoreTopTime = 900;
  driveForward(75, convertDistance(70), 1300);
  inertialRight(75, 126);
  driveForwardIntake(75, convertDistance(70), 1000);
  scoreTop(scoreOne, scoreTopTime);
  timeOuttake(100);
  driveBackward(75, convertDistance(70), 1500);
  inertialRight(75, 270);
  driveForward(100, convertDistance(125), 1400);
  inertialLeft(75, Inertial17.heading() - 89);
  driveForward(75, convertDistance(49), 600);
  sortBall(2, 1);
  stopAll();
  timeIntake(500);
  stopAll();
  driveBackward(75, convertDistance(40), 500);
}

void blueAutoSecondGoal() { // This auto goes up to sorting the 2nd goal
  int scoreOne = 1000;
  int scoreTopTime = 900;
  driveForward(75, convertDistance(70), 1300);
  inertialRight(75, 126);
  driveForwardIntake(75, convertDistance(70), 1000);
  scoreTop(scoreOne, scoreTopTime);
  timeOuttake(100);
  driveBackward(75, convertDistance(70), 1500);
  inertialRight(75, 270);
  driveForward(100, convertDistance(125), 1400);
  inertialLeft(75, Inertial17.heading() - 92);
  driveForward(75, convertDistance(49), 600);
  sortBall(2, 2);
  stopAll();
  timeIntake(500);
  stopAll();
  driveBackward(75, convertDistance(40), 500);
}
void blueAutoSecondOpposite() {
  int scoreOne = 1000;
  int scoreTopTime = 900;
  driveForward(75, convertDistance(70), 1300);
  inertialLeft(75, Inertial17.heading() - 126);
  driveForwardIntake(75, convertDistance(70), 1000);
  scoreTop(scoreOne, scoreTopTime);
  timeOuttake(100);
  driveBackward(75, convertDistance(70), 1500);
  inertialLeft(75, Inertial17.heading() - 270);
  driveForward(100, convertDistance(125), 1400);
  inertialRight(75, Inertial17.heading() + 92);
  driveForward(75, convertDistance(49), 600);
  sortBall(2, 2);
  stopAll();
  timeIntake(500);
  stopAll();
  driveBackward(75, convertDistance(40), 500);
}

// BLUE AUTONOMOUS BELOW

void blueAutoShuffle() { // Only shuffle sorting first goal
  driveForward(75, convertDistance(70),
               1300);     // Speed,Distance (motor degrees), Time Allocated
  inertialRight(75, 126); // Speed, Heading Position
  driveForwardIntake(65, convertDistance(75), 1000);
  shuffleSortBlue();
  stopAll();
}
void blueAutoShuffleOpposite() { // Only shuffle sorting first goal
  driveForward(75, convertDistance(70),
               1300);     // Speed,Distance (motor degrees), Time Allocated
  inertialRight(75, 229); // Speed, Heading Position
  driveForwardIntake(65, convertDistance(75), 1000);
  shuffleSortBlue();
  stopAll();
}

void blueAuton() {
  // 100 deg  = 9 cm
  // right positive left negative
  int scoreOne = 1000;
  int scoreTopTime = 900;
  // We need converDistance() surrounding the number to convert from centimeters
  // to motor units
  driveForward(75, convertDistance(70),
               1300);     // Speed,Distance (motor degrees), Time Allocated
  inertialRight(75, 126); // Speed, Heading Position
  driveForwardIntake(75, convertDistance(65), 1000);
  scoreTop(scoreOne,
           scoreTopTime); // Rotation,Time allocated (Defaults to MAX Speed)
  timeOuttake(100);       // milliseconds (Timing based outtake)
  driveBackward(75, convertDistance(70), 1500);
  inertialLeft(75, Inertial17.heading() -
                       144); // Speed, Heading //270-126 = diff of 144
  driveForward(100, convertDistance(116), 1100);
  inertialRight(75, Inertial17.heading() + 90);
  driveForward(75, convertDistance(40), 500);
  elevatorScoreTwo(1200, 800);
  stopAll();
  driveBackward(75, convertDistance(40), 500);
  inertialLeft(75, Inertial17.heading() - 86);
  driveForwardDrop(80, convertDistance(133), 1800);
  inertialRight(75, Inertial17.heading() + 45);
  driveForwardIntake(75, convertDistance(45), 500);
  sortBall(3, 2);
  stopAll();
  driveBackward(75, 400, 10000000);
}

void pidTest() {
  vex::task pidMovement(pidLoop);
  resetDriveEncoders = true;
  ktarget = 1000;
  turntarget = 0;
  vex::task::sleep(2000);
  resetTarget();
}
void driveForwardDropBallIntake(int speed, int rotation, int time) {
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  Elevator.setVelocity(speed, velocityUnits::pct);
  Elevator2.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
  Elevator.rotateFor(rotation, rotationUnits::rev, false);
  Elevator2.rotateFor(-rotation, rotationUnits::rev, false);
  IntakeR.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  task::sleep(time);
}

void descoreBall(int rot, int time) {
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(rot, rotationUnits::rev, false);
  Elevator2.rotateFor(-rot, rotationUnits::rev, false);
  vex::task::sleep(time);
  stopAll();
}

void deScoreScore(int rollDeg, int intakeDeg, int time) {
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  IntakeR.setVelocity(127, velocityUnits::pct);
  IntakeL.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(rollDeg, rotationUnits::deg, false);
  Elevator2.rotateFor(rollDeg, rotationUnits::deg, false);
  IntakeL.setVelocity(127, velocityUnits::pct);
  IntakeR.setVelocity(127, velocityUnits::pct);
  IntakeR.rotateFor(intakeDeg, rotationUnits::deg, false);
  IntakeL.rotateFor(intakeDeg, rotationUnits::deg, false);
  vex::task::sleep(time);
  stopAll();
}
void Score2(int rollDeg, int intakeDeg, int time) {
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(rollDeg, rotationUnits::deg, false);
  Elevator2.rotateFor(rollDeg, rotationUnits::deg, false);
  task::sleep(time);
  stopAll();
}
void skillsRouteB() {
  vex::task megaOof(speedometer);
  Elevator2.setVelocity(85, pct);
  Elevator2.rotateFor(0.5, rotationUnits::rev, true);
  driveForwardIntake(60, convertDistance(95), 1750);
  Inertial17.setHeading(90, deg);
  inertialRight(100, 216); // replace
  driveForward(100, convertDistance(135), 1600);
  Elevator2.setVelocity(100, pct);
  Elevator2.rotateFor(1800, rotationUnits::deg, true);
  deScoreScore(1500, 1100, 1400);
  driveBackwardOuttakeNoRoll(50, 800, 1300);
  stopAll();
  Inertial17.setHeading(90, deg);
  inertialLeft(75, 63); // 333
  driveBackwardOuttake(75, 600, 1000);
  stopAll();
  Inertial17.setHeading(90, deg);
  inertialLeft(100, 25);
  driveBackward(100, 1300, 2000);
  driveForwardIntake(70, 2345, 3000);
  Inertial17.setHeading(90, deg);
  inertialRight(100, 167);
  int ballUp = 700;
  elevatorScoreTwo(800, 800);
  driveForwardIntake(100, 1250, 1600);
  Elevator2.setVelocity(100, pct);
  Elevator2.rotateFor(1800, rotationUnits::deg, true);
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(2000, rotationUnits::deg, false);
  Elevator2.rotateFor(2000, rotationUnits::deg, false);
  task::sleep(1500);
  driveBackward(50, 400, 800);
  driveBackwardOuttakeNoRoll(50, 300, 800);
  Inertial17.setHeading(180, deg);
  inertialLeft(75, 110);
  driveForwardIntake(70, 1500, 2000);
  Inertial17.setHeading(90, deg);
  inertialRight(100, 130);
  driveForwardIntake(70, convertDistance(140), 1800);
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(2000, rotationUnits::deg, false);
  Elevator2.rotateFor(2000, rotationUnits::deg, false);
  task::sleep(2000);
  stopAll();

  driveBackwardOuttakeNoRoll(75, 1700, 2000);
  Inertial17.setHeading(180, deg);
  inertialLeft(75, 64);
  driveBackward(100, 3000, 2000);
  driveForwardIntake(70, 2340, 3100);
  stopAll();
  Inertial17.setHeading(90, deg);
  inertialRight(100, 167);
  driveForward(100, 1350, 1800);
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(2000, rotationUnits::deg, false);
  Elevator2.rotateFor(2000, rotationUnits::deg, false);
  task::sleep(2000);
  driveBackwardOuttakeNoRoll(50, 500, 1100);
  Inertial17.setHeading(180, deg);
  inertialLeft(75, 114);
  driveForwardIntake(70, 1720, 2500);
  Inertial17.setHeading(90, deg);
  inertialRight(100, 131);
  driveForwardIntake(70, convertDistance(110), 1300);
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(2000, rotationUnits::deg, false);
  Elevator2.rotateFor(2000, rotationUnits::deg, false);
  task::sleep(2000);

  stopAll();

  driveBackwardOuttakeNoRoll(50, 700, 1200);
  stopAll();
  Inertial17.setHeading(90, deg);
  inertialLeft(75, 63); // 333
  driveBackwardOuttake(75, 600, 1000);
  stopAll();
  Inertial17.setHeading(90, deg);
  inertialLeft(100, 23);
  driveBackward(100, 1300, 2000);
  driveForwardIntake(70, 2345, 3000);
  Inertial17.setHeading(180, deg);
  inertialLeft(100, 95);
  driveForwardIntake(100, 1000, 1400);
  LeftMotorF.setVelocity(127, velocityUnits::pct);
  LeftMotorB.setVelocity(127, velocityUnits::pct);
  LeftMotorB.rotateFor(700, rotationUnits::deg, false);
  LeftMotorF.rotateFor(700, rotationUnits::deg, false);
  task::sleep(1000);
  Inertial17.setHeading(90, deg);
  inertialRight(100, 23);
  Elevator.setVelocity(127, velocityUnits::pct);
  Elevator2.setVelocity(127, velocityUnits::pct);
  Elevator.rotateFor(2000, rotationUnits::deg, false);
  Elevator2.rotateFor(2000, rotationUnits::deg, false);
  task::sleep(2000);
  driveBackward(70, 1345, 1300);
  driveForwardIntake(100, 1250, 1600);
}
