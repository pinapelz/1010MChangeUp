#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ballSorter.h"
#include <string.h>
double offset = 15.4;
int JOYSTICK_DEADZONE = 5;
int ktarget = 0;
bool intakeBool = false;

int turntarget = 0;
int intakeSpeed = 100;
bool resetDriveEncoders = false;
using namespace vex;

void lockWheels() {
  LeftMotorB.stop(brakeType::coast);
  LeftMotorF.stop(brakeType::coast);
  RightMotorF.stop(brakeType::coast);
  RightMotorB.stop(brakeType::coast);
}
int expDrive(int joystickValue){
  int output = 0;
  if(abs(joystickValue) > JOYSTICK_DEADZONE){
    int direction = abs(joystickValue) / joystickValue;
    output = (int) (direction * (1.2 * pow(1.0356, abs(joystickValue)) - 1.2 + 0.2 * abs(joystickValue)));
  }
  return output;
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
    Brain.Screen.printAt(0,80,"Inertial Sensor Heading: %f", Inertial17.rotation(deg));
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

void driveForward(int speed, int rot, int time) { // Drive forward function that uses motor revrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);

//Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct); 
  
  vex::task::sleep(time);
  lockWheels();
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}

void driveForwardIntake(int speed, int rot, int time) { // Drive forward function that uses motor revrees
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

//Elevator.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct); 
  
  vex::task::sleep(time);
  lockWheels();
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void driveBackward(
  int speed, int rotation,
    int time) { // Drive backward function that uses motor revrees
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
void inertialLeft(int speed, float revreee) {
  while(Inertial17.heading(degrees) >= (revreee - 14.8)){
    LeftMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    RightMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }
  

  lockWheels();

  task::sleep(200);
}
void inertialRight(int speed, float revree) {
  LeftMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  waitUntil((Inertial17.heading(degrees) >= (revree - 14.8)));
  lockWheels();
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

void elevatorScoreTwo(int rotation, int time){
  Elevator.setVelocity(75, pct);
  Elevator2.setVelocity(75, pct);
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
  task::sleep(sec);
}
void scoreTop(int sec) {
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
    int encoderAverage = (LeftMotorF.position(deg) + RightMotorF.position(deg))/2;
    int error = target - encoderAverage;
    int derivative = error - previousError;
    double LateralmotorPower = (error * kP + totalError * kI + derivative * kD); 
    int turnDifference = LeftMotorF.position(deg) - RightMotorF.position(deg); 
    int terror = ttarget - turnDifference;
    int tderivative = terror - tpreviousError;
    double turnMotorPower = (terror * tkP + ttotalError * tkI + tderivative * tkD); 
    if (intakeBool == true) {
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower, voltageUnits::volt); 
      LeftMotorB.spin(directionType::fwd, LateralmotorPower + turnMotorPower, voltageUnits::volt);
      RightMotorF.spin(directionType::fwd, LateralmotorPower - turnMotorPower,voltageUnits::volt);
      RightMotorB.spin(directionType::fwd, LateralmotorPower - turnMotorPower,voltageUnits::volt);
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
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower, voltageUnits::volt);
      LeftMotorB.spin(directionType::fwd, LateralmotorPower + turnMotorPower, voltageUnits::volt);
      RightMotorF.spin(directionType::fwd, LateralmotorPower - turnMotorPower, voltageUnits::volt);
      RightMotorB.spin(directionType::fwd, LateralmotorPower - turnMotorPower, voltageUnits::volt);
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
double convertDistance(double distance){
  return distance*11.1;
}

void redAuton(){
  //100 deg  = 9 cm

elevatorScoreTwo(1300,1300); //Preset for bringing the ball up to the top but not scoring
ballLocated();//Get ball to the intakes
scoreTop(300);
ballLocated();
elevatorScoreTwo(1300,1300);

    /*driveForwardIntake(75,convertDistance(60),750);
    scoreTop(1000);
    sortBall(3);*/

}

void pidTest(){
  vex::task pidMovement(pidLoop);
  resetDriveEncoders = true;
  ktarget = 1000;
  turntarget = 0;
  vex::task::sleep(2000);

}