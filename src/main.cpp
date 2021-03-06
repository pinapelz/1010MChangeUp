// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         20              
// Elevator             motor         10              
// Inertial17           inertial      16              
// Vision19             vision        19              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         20              
// Elevator             motor         10              
// Inertial17           inertial      16              
// Vision19             vision        19              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         18              
// Elevator             motor         10              
// Inertial17           inertial      16              
// Vision19             vision        19              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         18              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision19             vision        19              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         10              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision19             vision        19              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         10              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision11             vision        11              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         19              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision11             vision        11              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         19              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision10             vision        10              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         14              
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         19              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision10             vision        10              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotorF           motor         15              
// RightMotorB          motor         13              
// RightMotorF          motor         12              
// LeftMotorB           motor         5               
// Controller1          controller                    
// IntakeR              motor         6               
// IntakeL              motor         7               
// Elevator2            motor         19              
// Elevator             motor         20              
// Inertial17           inertial      16              
// Vision10             vision        10              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "autonomousFunctions.h"
#include "vex.h"
#include <iostream>
int rotateImages();
using namespace vex;
void hasRedCallback();
void ballLocated();
void hasBlueCallback();
void skillsRoute();
void cubeDrive(int maxim, int multiplier);
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
void blueAuton();
void redAutoShuffle();
void blueAutoShuffle();
void redAutoSecondGoal();
void blueAutoSecondGoal();
void blueAutoShuffleOpposite();
void blueAutoSecondOpposite();
void driveForward(int speed, int rot, int time);
void inertialLeft(int speed, float degree);
void timeOuttake(int sec);
void timeScore(int sec);
int matchTimer();
void pidTest();
void calibrateInertial();
void intake(int time, int speed, int rotation);
int speedometer();
competition Competition;

void pre_auton(void) { vexcodeInit(); }

void autonomous(void) {
  // vex::task megaOof(speedometer);

  /*
  void redAuton();
void blueAuton();
void redAutoShuffle();
void blueAutoShuffle();
void redAutoSecondGoal();
void blueAutoSecondGoal();
void blueAutoSecondOpposite
Replace Below with whichever one you need to run.
Blue autos are just what we did but with turning and colour sorting reversed

If you need to change auto code go under autonomusFunctions.h and scroll to
bottom
  */
  Brain.Screen.setFont(vex::fontType::mono60);
  Brain.Screen.printAt(0, 40, "Calibrating Inertial...");
  calibrateInertial();
  Brain.Screen.printAt(0, 40, "Calibration Complete!");
  skillsRouteB();
}

void usercontrol(void) {
  bool partnerDrive = true;
  vex::task megaOof(speedometer);
  vex::task slideshow(rotateImages);
  // vex::task matchtime(matchTimer);

  int sortMode = 2;
  int formulaMultiplier = 4;
  int maxSpeed = 127;
  double driveMultiplier = 0.9;
  bool exponential = true;
  while (1) {
    expoDriveLeft(fwd,(Controller1.Axis3.value()+Controller1.Axis1.value()));
    expoDriveRight(fwd,(Controller1.Axis3.value()-Controller1.Axis1.value()));
    if (Controller1.ButtonDown.pressing()) {

      redAutoShuffle();
    // ' locateBallRed();
      // elevatorScoreTwo(950,720);
        //timeIntake(200);
   
    }
    if (partnerDrive) {
      if (Controller2.ButtonY.pressing()) {
        // Ball Sorting: pass 1 for drop blue, score red and 2 for the opposite
        sortBall(1, sortMode);
      } else if (Controller2.ButtonRight.pressing()) {
        sortBall(2, sortMode);
      } else if (Controller2.ButtonLeft.pressing()) {
        sortBall(3, sortMode);
      } else if (Controller2.ButtonX.pressing()) {
        sortBall(4, sortMode);
      }
    } else {
      if (Controller2.ButtonY.pressing()) {
        // Ball Sorting: pass 1 for drop blue, score red and 2 for the opposite
        sortBall(1, sortMode);
      } else if (Controller1.ButtonRight.pressing()) {
        sortBall(2, sortMode);
      } else if (Controller1.ButtonLeft.pressing()) {
        sortBall(3, sortMode);
      } else if (Controller1.ButtonX.pressing()) {
        sortBall(4, sortMode);
      }
    }
    if (Controller1.ButtonR1.pressing() || Controller2.ButtonR1.pressing()) {
      Elevator.spin(reverse, 100, pct);
      Elevator2.spin(reverse, 100, pct);
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);
    } else if (Controller1.ButtonR2.pressing() ||
               Controller2.ButtonR2.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(fwd, 100, pct);

    } else if (Controller1.ButtonA.pressing() ||
               Controller2.ButtonA.pressing()) {
      Elevator.spin(fwd, 100, pct);
      Elevator2.spin(reverse, 100, pct);
    } else if (Controller1.ButtonX.pressing() ||
               Controller2.ButtonX.pressing()) {
      Elevator.spin(fwd, 100, pct);
    } else if (Controller1.ButtonB.pressing() ||
               Controller2.ButtonB.pressing()) {
      Elevator.spin(reverse, 100, pct);
    }

    else {
      Elevator.stop();
      Elevator2.stop();
    }
    if (Controller1.ButtonL2.pressing() || Controller2.ButtonL2.pressing()) {
      IntakeL.spin(fwd, 100, pct);
      IntakeR.spin(fwd, 100, pct);

    }

    else if (Controller1.ButtonL1.pressing() ||
             Controller2.ButtonL1.pressing()) {
      IntakeL.spin(reverse, 100, pct);
      IntakeR.spin(reverse, 100, pct);

    } else {
      IntakeL.stop();
      IntakeR.stop();
    }

    if (!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing() &&
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