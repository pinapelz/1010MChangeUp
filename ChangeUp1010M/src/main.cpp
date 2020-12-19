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
// LeftMotorB           motor         3               
// RightMotorF          motor         12              
// RightMotorB          motor         5               
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         1               
// Elevator2            motor         19              
// Elevator             motor         18              
// Inertial17           inertial      17              
// Vision10             vision        10              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "autonomousFunctions.h"
#include "vex.h"
#include <iostream>
void resetEncoders();
int rotateImages();
using namespace vex;
event checkRed = event();
void hasRedCallback();
void hasBlueCallback();
void sortBall();
void driveForward(int speed, int rot, int time);
int matchTimer();
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

// A global instance of competition
competition Competition;

void pre_auton(void) {
  vexcodeInit();
  calibrateInertial();
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void resetTarget() {
  ktarget = 0;
  turntarget = 0;
}
void autonomous(void) {
   inertialRight(50, 180.0); 
   }



void usercontrol(void) {
 // vex::task megaOof(speedometer);

  // vex::task slideshow(rotateImages);
  vex::task matchtime(matchTimer);

  double driveMultiplier = 0.5;
  int deadband = 5;
  
  while (1) {

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
    if (Controller1.ButtonUp.pressing()) {
      driveMultiplier = 1.0;

    } else if (Controller1.ButtonDown.pressing()) {
      driveMultiplier = 0.5;
    }
    else if(Controller1.ButtonY.pressing()){
      sortBall();
    }
    if (Controller1.ButtonR1.pressing()) {
      Elevator.spin(reverse, 100, pct);
      Elevator2.spin(reverse, 100, pct);
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(fwd, 100, pct);
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);
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
         // checkBlue.broadcastAndWait();
  
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
