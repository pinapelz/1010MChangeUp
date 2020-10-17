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
// Intake               motor         5               
// Elevator             motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "autonomousFunctions.h"
#include "vex.h"

void resetEncoders();
using namespace vex;
bool resetEncoder = false;
bool runPid =true;
bool intake = false;
int ktarget = 0;
int turntarget = 0;
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
      intake = false;
      resetEncoders();
}

int target = ktarget;
int previousError = 0;
int totalError = 0;
int ttarget = turntarget;
int tpreviousError = 0;
int ttotalError = 0;

/*
Tune kP until steady minor oscillation
Tune kD increase until oscillation doesn't exist
Tune kI to increase position
*/

double kP = 0.2; //move to error less than 0.4
double kI = 0; //minor change
double kD = 0.1;//speed changes
double tkP = 0.13;
double tkI = 0;
double tkD = 0.01;
    int encoderAverage = (LeftMotorF.position(deg) + RightMotorF.position(deg)) / 2; //Current Encoder Position Average
    int error = target - encoderAverage;
    int derivative = error - previousError;
   // totalError += error; //Integral take it out if not needed
    double LateralmotorPower = (error * kP + totalError * kI + derivative * kD); // Add values up
  //Code for turning PID Below
    int turnDifference = LeftMotorF.position(deg) - RightMotorF.position(deg); //Current Encode Position
    int terror = ttarget- turnDifference; //Potentional
    int tderivative = terror - tpreviousError; //Derivative
   // ttotalError += terror; //Integral take it out if not needed
    double turnMotorPower = (terror * tkP + ttotalError * tkI + tderivative * tkD); // Add values up
  //Code for Motor Movements
  if(intake==true){
    LeftMotorF.spin(directionType::fwd, LateralmotorPower+turnMotorPower, voltageUnits::volt);//Run the voltage
    LeftMotorB.spin(directionType::fwd, LateralmotorPower+turnMotorPower, voltageUnits::volt);
    RightMotorF.spin(directionType::fwd, LateralmotorPower-turnMotorPower, voltageUnits::volt);
    RightMotorB.spin(directionType::fwd, LateralmotorPower-turnMotorPower, voltageUnits::volt);
    Intake.spin(forward,100,pct);
    previousError = error;
    tpreviousError = terror;
        Brain.Screen.setCursor(2,0);
        Brain.Screen.printAt(1, 20, "Turning Power %f",turnMotorPower);
        Brain.Screen.printAt(1, 40, "Lateral Power%f",LateralmotorPower);
        Brain.Screen.printAt(1,60,"Turning Distance Remaining%f",terror);

    task::sleep(20);
  }
  else if(intake==false){
    LeftMotorF.spin(directionType::fwd, LateralmotorPower+turnMotorPower, voltageUnits::volt);//Run the voltage
    LeftMotorB.spin(directionType::fwd, LateralmotorPower+turnMotorPower, voltageUnits::volt);
    RightMotorF.spin(directionType::fwd, LateralmotorPower-turnMotorPower, voltageUnits::volt);
    RightMotorB.spin(directionType::fwd, LateralmotorPower-turnMotorPower, voltageUnits::volt);
    previousError = error;
    tpreviousError = terror;
        Brain.Screen.setCursor(2,0);
        Brain.Screen.printAt(1, 20, "Turning Power %f",turnMotorPower);
        Brain.Screen.printAt(1, 40, "Lateral Power%f",LateralmotorPower);
        Brain.Screen.printAt(1,60,"Turning Distance Remaining%f",terror);

    task::sleep(20);
  }
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
void resetTarget(){
  ktarget = 0;
  turntarget = 0;
}
void autonomous(void) {
  vex::task something(pidTestForward);
  resetEncoder = true;
  intake = true;
  turntarget = 1000;
  task::sleep(2000);
  
  resetEncoder = true;
  intake = false;
  ktarget = 1000;


 
}

void usercontrol(void) {
  int deadband = 5;
  while (1) {
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
      RightMotorB.setVelocity(rightMotorSpeed, pct);
    }

    LeftMotorF.spin(fwd);
    LeftMotorB.spin(fwd);
    RightMotorF.spin(fwd);
    RightMotorB.spin(fwd);
    if(Controller1.ButtonR1.pressing()){
      Intake.spin(fwd,100,pct);

    }

    else if(Controller1.ButtonR2.pressing()){
    Intake.spin(reverse,100,pct);
    
    }
    else{
      Intake.stop(coast);
    }
    if(Controller1.ButtonL1.pressing()){
      Elevator.spin(forward,100,pct);
    }
    else if(Controller1.ButtonL2.pressing()){
      Elevator.spin(reverse,100,pct);
    }
    else{
      Elevator.stop();
    }
        Brain.Screen.printAt(1, 20, "Left Front Temp %f pct",LeftMotorF.temperature(pct));
        Brain.Screen.printAt(1, 40, "Left Back Temp %f pct",LeftMotorB.temperature(percent));
        Brain.Screen.printAt(1,60,"Right Front Temp %f pct",RightMotorF.temperature(percent));
         Brain.Screen.printAt(1,80,"Right Back Temp %f pct",RightMotorB.temperature(percent));
        Brain.Screen.printAt(1,100,"50 percent or above is BAD");
  }

  
}

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
