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
// LeftMotorB           motor         2               
// RightMotorF          motor         12              
// RightMotorB          motor         5               
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         1               
// Elevator2            motor         19              
// Elevator             motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "autonomousFunctions.h"
#include "vex.h"
#include <iostream>
void resetEncoders();
using namespace vex;
void driveForward(int speed, int rot, int time);
bool resetEncoder = false;
bool runPid = true;
bool intakeBool = true;
int intakeSpeed = 0;
int intakeDegrees = 0;
int ktarget = 0;
int count = 0;
int turntarget = 0;
int kturntarget = 0;

// A global instance of competition
competition Competition;

int pidLoop() {
  while (runPid) {
    if (resetEncoder) {
      resetEncoder = false;
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
    double kP = 0.2; // move to error less than 0.4
    double kI = 0;   // minor change
    double kD = 0.1; // speed changes
    double tkP = 0.13;
    double tkI = 0;
    double tkD = 0.01;
    int encoderAverage = (LeftMotorF.position(deg) + RightMotorF.position(deg));
    int error = target - encoderAverage;
    int derivative = error - previousError;
    // totalError += error; //Integral take it out if not needed
    double LateralmotorPower = (error * kP + totalError * kI + derivative * kD); // Add values up
    /*

    Turning PID

    */
    int turnDifference = LeftMotorF.position(deg) - RightMotorF.position(deg); // Encoder Position
    int terror = ttarget - turnDifference;
    int tderivative = terror - tpreviousError;
    // ttotalError += terror; //Integral take it out if not needed
    double turnMotorPower = (terror * tkP + ttotalError * tkI + tderivative * tkD); 
    if (intakeBool == true) {
      //redundant but won't work without it
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower, voltageUnits::volt); // Run the voltage
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
    Brain.Screen.setCursor(2,0);
    Brain.Screen.printAt(1, 20, "Turning Power %f", turnMotorPower);
    Brain.Screen.printAt(1, 40, "Lateral Power%f", LateralmotorPower);
    Brain.Screen.printAt(1, 60, "Turning Distance Remaining%f", terror);

    task::sleep(20);
  }
  return 1;
}

void pre_auton(void) {
  vexcodeInit();
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
  vex::task blahblahblah(pidLoop);
  // driveForward(50,1000,1000);
  intakeBool = true;
  intakeSpeed = 50; // in percentage
  turntarget = 0;
  ktarget = 1000;
  task::sleep(1300);

  resetEncoder = true;
  intakeBool = false;
  intakeSpeed = 0;
  ktarget = 0;
  turntarget = 500;
  task::sleep(1000);
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
int matchTimer(){
  //128x64
  bool matchOver=false;
  int timeRemaining = 105;
  int minutesLeft = timeRemaining/60;
  int secondsLeft = timeRemaining%60;

  while(!matchOver){
    
    Controller1.Screen.setCursor(6,0);
    Controller1.Screen.clearLine(4);
    minutesLeft = timeRemaining/60;
    secondsLeft = timeRemaining%60;
    Controller1.Screen.print("Match Time: ");
    Controller1.Screen.print(minutesLeft);
    Controller1.Screen.print(":");
    Controller1.Screen.print(secondsLeft);
    vex::task::sleep(1000);
    timeRemaining--;
    switch(timeRemaining){
      case 60:
        Controller1.rumble("-");
        Controller1.Screen.setCursor(6,0);
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
int speedometer(){
  Brain.Screen.setFont(propM);
  
  while(true){
   Brain.Screen.printAt(0, 40, "Elevator 1 RPM: %f", Elevator.velocity(rpm));
      Brain.Screen.printAt(0, 60, "Elevator 2 RPM: %f", Elevator2.velocity(rpm));
   task::sleep(300);
  }
   return 0;
}
void usercontrol(void) {
  //vex::task megaOof(speedometer);
vex::task slideshow(rotateImages);
 vex::task matchtime(matchTimer);

  double driveMultiplier = 0.5;
  int deadband = 5;
  while (1) {
    
    
    int leftMotorSpeed = (Controller1.Axis3.position() + Controller1.Axis1.position())*driveMultiplier;
    int rightMotorSpeed = (Controller1.Axis3.position() - Controller1.Axis1.position())*driveMultiplier;


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
    if(Controller1.ButtonUp.pressing()){
      driveMultiplier = 1.0;

    }
    else if(Controller1.ButtonDown.pressing()){
      driveMultiplier = 0.5;
    }
    


    if(Controller1.ButtonL1.pressing()){
      IntakeL.spin(fwd,100,pct);
      IntakeR.spin(fwd,100,pct);
      Elevator.spin(fwd,100,pct);
      Elevator2.spin(fwd,100,pct);
    }
 
    else if(Controller1.ButtonL2.pressing()){
      IntakeL.spin(reverse,100,pct);
      IntakeR.spin(reverse,100,pct);
      Elevator.spin(reverse,100,pct);
      Elevator2.spin(reverse,100,pct);
    }
    else if(Controller1.ButtonA.pressing()){
      Elevator.spin(fwd,75,pct);
      Elevator2.spin(reverse,75,pct);
    }
  else{
    IntakeL.stop();
    IntakeR.stop();
    Elevator.stop();
    Elevator2.stop();

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
