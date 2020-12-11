#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
double offset = 15.4;
using namespace vex;
void lockWheels(){
  LeftMotorB.stop(brakeType::hold);
  LeftMotorF.stop(brakeType::hold);
  RightMotorF.stop(brakeType::hold);
  RightMotorB.stop(brakeType::hold);
}




void driveForward(int speed, int rot, int time) { // Drive forward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);
Brain.Screen.printAt(1, 60, "Turning Distance Remaining%f", 21);
  LeftMotorF.rotateFor(rot, rotationUnits::deg, false);
  RightMotorF.rotateFor(rot, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rot, rotationUnits::deg, false);
  RightMotorB.rotateFor(rot, rotationUnits::deg, false);
  vex::task::sleep(time);

}


void driveBackward(int speed,int rotation,int time) { // Drive backward function that uses motor degrees
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


void driveRight(int speed, int rotation,int time) { // Turn right using motor degrees

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
void intake(int time,int speed, int rotation) { 
  IntakeL.setVelocity(speed, velocityUnits::pct);
  IntakeR.setVelocity(speed, velocityUnits::pct);

  IntakeL.rotateFor(rotation, rotationUnits::deg, false);
  IntakeR.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
  
}
void calibrateInertial(){
    Inertial17.calibrate();
  while (Inertial17.isCalibrating()) {
    wait(100, msec);
  }
}
void inertialLeft(int speed, float degree){
  
   LeftMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
   RightMotorF.spin(vex::directionType::fwd,speed, vex::velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    waitUntil((Inertial17.rotation(degrees) >= (degree-14.8)));
    lockWheels();
    task::sleep(200);
    
}
void inertialRight(int speed, float degree){
   LeftMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
   RightMotorF.spin(vex::directionType::rev,speed, vex::velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    waitUntil((Inertial17.rotation(degrees) >= (degree-14.8)));
    lockWheels();
    task::sleep(200);
    
}
void driveLeft(int speed,int rotation,int time) { // Turn left using motor degrees

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



void intakeScore(int time){
    IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
    Elevator.spin(fwd,100,pct);
  Elevator2.spin(fwd,100,pct);
  task::sleep(time);
  IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
}
void TimeScore(int sec){
  Elevator.spin(fwd,100,pct);
  Elevator2.spin(fwd,100,pct);
  task::sleep(sec);

 
}

void TimeIntake(int sec){
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
  vex::task::sleep(sec); //2700
}












void resetEncoders() {
  LeftMotorF.resetPosition();
  LeftMotorB.resetPosition();
  RightMotorF.resetPosition();
  RightMotorB.resetPosition();
}