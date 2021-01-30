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
#include "ballSorter.h"
#include <iostream>
void resetEncoders();
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
void driveForwardIntake(int speed, int rot,int time); 
void driveBackward(int speed, int rotation, int time);
void sortBall(int count);
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
bool resetEncoder = false;
bool runPid = true;
bool intakeBool = true;
int speedometer();
int intakeSpeed = 0;
int intakeDegrees = 0;
int ktarget = 0;
bool usingIntake = false;
int count = 0;
int turntarget = 0;
int kturntarget = 0;
competition Competition;

void pre_auton(void) {
  vexcodeInit();
}


void resetTarget() {
  ktarget = 0;
  turntarget = 0;
}
void autonomous(void) {
  vex::task megaOof(speedometer);
  redAuton();
}

void usercontrol(void) {
  vex::task megaOof(speedometer);
  // vex::task slideshow(rotateImages);
  vex::task matchtime(matchTimer);

  double driveMultiplier = 0.75;
  int deadband = 5;
  bool exponential = true;
  while (1) {
    if(!exponential){
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
    else{
      int leftSpeed = getExpoValue(controllerY+controllerX);
      int rightSpeed = getExpoValue(controllerY-controllerX);
      LeftMotorF.spin(fwd,leftSpeed,pct);
      LeftMotorB.spin(fwd,leftSpeed,pct);
      RightMotorF.spin(fwd,rightSpeed,pct);
      RightMotorB.spin(fwd,rightSpeed,pct);

    }
    if (Controller1.ButtonUp.pressing()) {
      driveMultiplier = 1.0;

    } else if (Controller1.ButtonDown.pressing()) {
      driveMultiplier = 0.5;
    }
    else if(Controller1.ButtonY.pressing()){
      sortBall(1);
    }
    else if(Controller1.ButtonRight.pressing()){
      sortBall(2);
    }
    else if(Controller1.ButtonLeft.pressing()){
      sortBall(3);
    }
    else if(Controller1.ButtonX.pressing()){
      sortBall(4);
    }
    if (Controller1.ButtonR1.pressing()) {
      Elevator.spin(reverse, 100, pct);
      Elevator2.spin(reverse, 100, pct);
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(fwd, 100, pct);

    } else if (Controller1.ButtonA.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(reverse, 100, pct);
    } else if (Controller1.ButtonX.pressing()) {
      Elevator.spin(fwd, 100, pct);
    } else if (Controller1.ButtonB.pressing()) {
      Elevator.spin(reverse, 100, pct);
    }

    else {
      Elevator.stop();
      Elevator2.stop();
    }
    if (Controller1.ButtonL2.pressing()) {
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);

    }

    else if (Controller1.ButtonL1.pressing()) {
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

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
