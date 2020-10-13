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
// LeftMotorF           motor         1               
// LeftMotorB           motor         2               
// RightMotorF          motor         3               
// RightMotorB          motor         4               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "autonomousFunctions.h"
#include "vex.h"

void resetEncoders();
using namespace vex;
bool resetEncoder = false;
bool runPid =true;
int ktarget = 0;
int kturntarget = 0;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int pidTestForward() {
  while (runPid) {
    if (resetEncoder) {
      resetEncoder = false;
      resetEncoders();
    }

    int target = ktarget;
    int previousError = 0;
    int totalError = 0;

    // Tune here
double kP = 0.03;
double kI = 0.043;
double kD = 0.3;
    int encoderAverage = (LeftMotorF.position(deg) + RightMotorF.position(deg)) / 2;
    int error = target-encoderAverage;
    int derivative = error - previousError;

    int LateralmotorPower = (error * kP + totalError * kI + derivative * kD); // Add values up
   
    LeftMotorF.spin(directionType::fwd, LateralmotorPower, voltageUnits::volt);
    LeftMotorB.spin(directionType::fwd, LateralmotorPower, voltageUnits::volt);
    RightMotorF.spin(directionType::fwd, LateralmotorPower, voltageUnits::volt);
    RightMotorB.spin(directionType::fwd, LateralmotorPower, voltageUnits::volt);
    previousError = error;
        Brain.Screen.setCursor(2,0);
        //LeftMotorF.position(degrees)
        Brain.Screen.printAt(1, 20, "in loop, we are at %d",LateralmotorPower);
    task::sleep(20);
  }
  return 1;
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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

void autonomous(void) {
  vex::task something(pidTestForward);
  resetEncoder = true;
  ktarget = -1000;
  task::sleep(2000);
  ktarget = 500;
}

void usercontrol(void) {
  int deadband = 5;
  while (1) {

    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    int leftMotorSpeed =
        Controller1.Axis3.position() + Controller1.Axis1.position();
    int rightMotorSpeed =
        Controller1.Axis3.position() - Controller1.Axis1.position();

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
      RightMotorB.setVelocity(0, pct);
    }

    LeftMotorF.spin(fwd);
    LeftMotorB.spin(fwd);
    RightMotorF.spin(fwd);
    RightMotorB.spin(fwd);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
