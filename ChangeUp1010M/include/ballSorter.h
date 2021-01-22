#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool seenRed = false;
int ballsProcessed = 0;
void stopAll(){
    IntakeR.stop();
  IntakeL.stop();
  Elevator.stop();
  Elevator2.stop();
  task::sleep(10);
}
void setRed(bool red){
seenRed = red;
}
void releaseBall(int time, int revo){

    Elevator.setVelocity(-127, pct);
    Elevator2.setVelocity(-127, pct);

  Elevator.rotateFor(revo, rotationUnits::rev, false);
  Elevator2.rotateFor(-revo, rotationUnits::rev, false);
  task::sleep(time);
}
void elevatorScore(int time, int revolution){
      Elevator.setVelocity(127, pct);
    Elevator2.setVelocity(127, pct);
  Elevator.rotateFor(revolution, rotationUnits::rev, false);
  Elevator2.rotateFor(revolution, rotationUnits::rev, false);
  task::sleep(time);
  Elevator2.stop(brake);

}
void hasBlueCallbackSkillsAuto() {
  Vision10.takeSnapshot(Vision10__BLUEBALL);
  if (Vision10.objectCount > 0) {
    while (Vision10.objectCount > 0) {
      Vision10.takeSnapshot(Vision10__BLUEBALL);
      IntakeL.stop();
      IntakeR.stop();
      Elevator.spin(fwd, 75, pct);
      Elevator2.spin(reverse, 100, pct);
      if (Controller1.ButtonL2.pressing()) {
        IntakeL.spin(fwd, 100, pct);
        IntakeR.spin(fwd, 100, pct);
      }

    }

  }

  Vision10.takeSnapshot(Vision10__REDBALL);

  if (Vision10.objectCount > 0) {
    Controller1.rumble("...");
    while (Vision10.objectCount > 0) {
      Vision10.takeSnapshot(Vision10__REDBALL);
        IntakeL.spin(fwd, 100, pct);
        IntakeR.spin(fwd, 100, pct);
        task::sleep(300);
      IntakeL.stop();
      IntakeR.stop();
      Elevator.spin(forward, 75, pct);
      Elevator2.spin(fwd, 100, pct);

    }
    seenRed = true;

  }


}






/*
void hasBlueCallback() {
bool stopNow = false;

  Vision10.takeSnapshot(Vision10__BLUEBALL);
  if (Vision10.objectCount > 0) {

    while (Vision10.objectCount > 0) {
      Vision10.takeSnapshot(Vision10__BLUEBALL);
      if(Controller1.ButtonLeft.pressing()){ 
        stopNow = true;
      }
      IntakeL.stop();
      IntakeR.stop();
      Elevator.spin(fwd, 75, pct);
      Elevator2.spin(reverse, 100, pct);
      if (Controller1.ButtonL2.pressing()) {
      }
      if(stopNow){
        return;
      }
      vex::task::sleep(300);
    }

    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__REDBALL);

  if (Vision10.objectCount > 0) {
    while (Vision10.objectCount > 0) {
      Vision10.takeSnapshot(Vision10__REDBALL);
      IntakeL.stop();
      IntakeR.stop();
      Elevator.spin(forward, 75, pct);
      Elevator2.spin(fwd, 100, pct);
      if (Controller1.ButtonL2.pressing()) {
        IntakeL.spin(fwd, 100, pct);
        IntakeR.spin(fwd, 100, pct);
      }
      if(Controller1.ButtonLeft.pressing()){
        stopNow = true;
      }
      if(stopNow){
        return;
      }
      vex::task::sleep(400);
    }
    IntakeL.spin(fwd, 100, pct);
    IntakeR.spin(fwd, 100, pct);
    Elevator2.stop();
    Elevator.stop();
  }
        if(Controller1.ButtonLeft.pressing()){
        stopNow = true;
      }
      if(stopNow){
        return;
      }
  IntakeL.spin(fwd, 100, pct);
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();
  Elevator.stop();
  task::sleep(500);
}
*/
void hasBlueCallback() {
bool stopNow = false;
  Vision10.takeSnapshot(Vision10__BLUEBALL);
  if (Vision10.objectCount > 0) {
      IntakeL.stop();
      IntakeR.stop();
      releaseBall(1000,3);
      ballsProcessed++;
    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__REDBALL);

  if (Vision10.objectCount > 0) {
          IntakeL.stop();
      IntakeR.stop();
      elevatorScore(1300,5);
      ballsProcessed++;
  }
  if(Controller1.ButtonB.pressing()){
    return;
  }
  IntakeL.spin(fwd, 100, pct);
  IntakeR.spin(fwd, 100, pct);
    Elevator.spin(fwd,100,pct);
  Elevator2.stop();

}







void hasRedCallback() {


  Vision10.takeSnapshot(Vision10__BLUEBALL);
  if (Vision10.objectCount > 0) {
    while (Vision10.objectCount > 0) {
      Vision10.takeSnapshot(Vision10__BLUEBALL);

      IntakeL.stop();
      IntakeR.stop();
      Elevator.spin(fwd, 75, pct);
      Elevator2.spin(reverse, 100, pct);
      if (Controller1.ButtonL2.pressing()) {
        IntakeL.spin(fwd, 100, pct);
        IntakeR.spin(fwd, 100, pct);
      }
      vex::task::sleep(300);
    }

    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__REDBALL);

  if (Vision10.objectCount > 0) {
    while (Vision10.objectCount > 0) {
      Vision10.takeSnapshot(Vision10__REDBALL);
        IntakeL.spin(fwd, 100, pct);
        IntakeR.spin(fwd, 100, pct);
        task::sleep(300);
      IntakeL.stop();
      IntakeR.stop();
      Elevator.spin(forward, 75, pct);
      Elevator2.spin(fwd, 100, pct);
      if (Controller1.ButtonL2.pressing()) {
        IntakeL.spin(fwd, 100, pct);
        IntakeR.spin(fwd, 100, pct);
      }
      vex::task::sleep(400);
    }
    IntakeL.spin(fwd, 100, pct);
    IntakeR.spin(fwd, 100, pct);
    Elevator2.stop();
    Elevator.stop();
  }

  IntakeL.spin(fwd, 100, pct);
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();
  Elevator.stop();
  task::sleep(500);
  }


void sortBallSkillsAuto(){
    event checkBlue = event();
  event checkRed = event();
  checkBlue(hasBlueCallbackSkillsAuto);
  checkRed(hasRedCallback);

  while (!seenRed) {
    checkBlue.broadcastAndWait();
  }
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  Elevator.spin(reverse, 100, pct);
  Elevator2.spin(reverse, 100, pct);
  vex::task::sleep(800);   
  stopAll();
}

void sortBallAuto(){
    event checkBlue = event();
  event checkRed = event();
  checkBlue(hasBlueCallbackSkillsAuto);
  checkRed(hasRedCallback);

  while (!seenRed) {
    checkBlue.broadcastAndWait();
  }
  stopAll();
}
void sortBall(int process) {
  ballsProcessed = 0;
  event checkBlue = event();
  event checkRed = event();
  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  while (process!=ballsProcessed||!Controller1.ButtonB.pressing()) {
    checkBlue.broadcastAndWait();
  }
}
