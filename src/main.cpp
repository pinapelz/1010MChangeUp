// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         3               
// RightMotorF          motor         12              
// LeftMotorB           motor         5               
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         1               
// Elevator2            motor         19              
// Elevator             motor         20              
// Inertial17           inertial      17              
// Vision10             vision        10              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15
// RightMotorB          motor         3
// RightMotorF          motor         12
// LeftMotorB           motor         5
// Controller1          controller
// IntakeR              motor         6
// IntakeL              motor         1
// Elevator2            motor         19
// Elevator             motor         20
// Inertial17           inertial      17
// Vision10             vision        10
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "autonomousFunctions.h"
#include "vex.h"
#include <iostream>
int rotateImages();
using namespace vex;
event checkRed = event();
void elevatorScoreTwo(int rot, int time);
void setRed(bool red);
void scoreTop(int time);
void hasRedCallback();
void ballLocated();
void hasBlueCallback();
int expDrive(int joyVal);
void stopAll();
void intakeScore(int time, int rotation);
void elevatorScore(int time, int rotation);
void driveForwardIntake(int speed, int rot, int time);
void driveBackward(int speed, int rotation, int time);
void sortBall(int count, int colour);
void releaseBall(int time, int speed, int rotation);
void holdBall(int time, int speed, int rotation);
void inertialRight(int speed, float degree);
void redAuton();
void driveForward(int speed, int rot, int time);
void inertialLeft(int speed, float degree);
void timeOuttake(int sec);
void timeScore(int sec);
int matchTimer();
void pidTest();
void calibrateInertial();
void intake(int time, int speed, int rotation);
bool runPid = true;
int speedometer();
competition Competition;

void pre_auton(void) { vexcodeInit(); }

void autonomous(void) {
  vex::task megaOof(speedometer);
  redAuton();
}

void usercontrol(void) {
  bool partnerDrive  = true;
  vex::task megaOof(speedometer);
   vex::task slideshow(rotateImages);
  vex::task matchtime(matchTimer);

  double driveMultiplier = 0.9;
  int deadband = 5;
  bool exponential = false;
  while (1) {
    if (!exponential) {
      int leftMotorSpeed =
          (Controller1.Axis3.position() + Controller1.Axis1.position()) *
          driveMultiplier;
      int rightMotorSpeed =
          (Controller1.Axis3.position() - Controller1.Axis1.position()) *
          driveMultiplier;

      if (abs(leftMotorSpeed) < deadband) {
        LeftMotorF.setVelocity(0, pct);
        LeftMotorB.setVelocity(0, pct);
      } else {
        LeftMotorF.setVelocity(leftMotorSpeed, pct);
        LeftMotorB.setVelocity(leftMotorSpeed, pct);
      }

      if (abs(rightMotorSpeed) < deadband) {
        RightMotorF.setVelocity(0, pct);
        RightMotorB.setVelocity(0, pct);
      } else {
        RightMotorF.setVelocity(rightMotorSpeed, pct);
        RightMotorB.setVelocity(rightMotorSpeed, pct);
      }
      LeftMotorF.spin(fwd);
      LeftMotorB.spin(fwd);
      RightMotorF.spin(fwd);
      RightMotorB.spin(fwd);

    }
    
    
     else {
        int leftSpeed = expDrive(Controller1.Axis3.position() + Controller1.Axis1.position());
      int rightSpeed =
          expDrive(Controller1.Axis3.position() - Controller1.Axis1.position());
      LeftMotorF.spin(fwd, leftSpeed, pct);
      LeftMotorB.spin(fwd, leftSpeed, pct);
      RightMotorF.spin(fwd, rightSpeed, pct);
      RightMotorB.spin(fwd, rightSpeed, pct);
      }

    
    if (Controller1.ButtonUp.pressing()) {
      driveMultiplier = 1.0;

    } else if (Controller1.ButtonDown.pressing()) {
      redAuton();
    } 
  
   if(partnerDrive){
    if (Controller2.ButtonY.pressing()) {
      //Ball Sorting: pass 1 for drop blue, score red and 2 for the opposite
      sortBall(1,1);
    } else if (Controller2.ButtonRight.pressing()) {
      sortBall(2,1);
    } else if (Controller2.ButtonLeft.pressing()) {
      sortBall(3,1);
    } else if (Controller2.ButtonX.pressing()) {
      sortBall(4,1);
    }
   }
    else{
    if (Controller2.ButtonY.pressing()) {
      //Ball Sorting: pass 1 for drop blue, score red and 2 for the opposite
      sortBall(1,1);
    } else if (Controller1.ButtonRight.pressing()) {
      sortBall(2,1);
    } else if (Controller1.ButtonLeft.pressing()) {
      sortBall(3,1);
    } else if (Controller1.ButtonX.pressing()) {
      sortBall(4,1);
    }
   }
    if (Controller1.ButtonR1.pressing()||Controller2.ButtonR1.pressing()) {
      Elevator.spin(reverse, 100, pct);
      Elevator2.spin(reverse, 100, pct);
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);
    } else if (Controller1.ButtonR2.pressing()||Controller2.ButtonR2.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(fwd, 100, pct);

    } else if (Controller1.ButtonA.pressing()||Controller2.ButtonA.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(reverse, 100, pct);
    } else if (Controller1.ButtonX.pressing()||Controller2.ButtonX.pressing()) {
      Elevator.spin(fwd, 100, pct);
    } else if (Controller1.ButtonB.pressing()||Controller2.ButtonB.pressing()) {
      Elevator.spin(reverse, 100, pct);
    }

    else {
      Elevator.stop();
      Elevator2.stop();
    }
    if (Controller1.ButtonL2.pressing()||Controller2.ButtonL2.pressing()) {
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);

    }

    else if (Controller1.ButtonL1.pressing()||Controller2.ButtonL1.pressing()) {
      IntakeL.spin(reverse, 100, pct);
      IntakeR.spin(reverse, 100, pct);

    }

    else if (!Controller1.ButtonL1.pressing() &&
             !Controller1.ButtonL2.pressing() &&
             !Controller1.ButtonR2.pressing()) {
      IntakeL.stop();
      IntakeR.stop();
    }
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
