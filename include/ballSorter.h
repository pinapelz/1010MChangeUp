#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool seenRed = false;
bool seenBallRed = false;
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
void hasBlueCallback() {
  Vision10.takeSnapshot(Vision10__BLUEBALL);
  if (Vision10.objectCount > 0) {
      IntakeL.stop();
      IntakeR.stop();
      releaseBall(500,3);
      ballsProcessed++;
    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__REDBALL);

  if (Vision10.objectCount > 0) {
          IntakeL.stop();
      IntakeR.stop();
      elevatorScore(800,5);
      ballsProcessed++;
  }

  IntakeL.spin(fwd, 100, pct);
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();

}


void seenRedBall(){
  while(true){
  Vision10.takeSnapshot(Vision10__REDBALL);
  if (Vision10.objectCount > 0) {
    Controller1.rumble(rumbleLong);
    seenBallRed = true;
    break;
  }
  IntakeL.spin(fwd, 100, pct);
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();
  }
}






void hasRedCallback() {
  Vision10.takeSnapshot(Vision10__REDBALL);
  if (Vision10.objectCount > 0) {
      IntakeL.stop();
      IntakeR.stop();
      releaseBall(500,3);
      ballsProcessed++;
    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__BLUEBALL);

  if (Vision10.objectCount > 0) {
          IntakeL.stop();
      IntakeR.stop();
      elevatorScore(800,5);
      ballsProcessed++;
  }

  IntakeL.spin(fwd, 100, pct);
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();

}






void ballLocated(){
  seenBallRed = false;
event redFind= event();
redFind(seenRedBall);
while(seenBallRed == false){
redFind.broadcastAndWait();
}
}
void sortBall(int process, int colour) {
  ballsProcessed = 0;
  event checkBlue = event();
  event checkRed = event();
  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  while (process!=ballsProcessed) {
    if(ballsProcessed==10){
      stopAll();
      break;
    }
    if(colour == 1){
      //Score Red Balls and Drop Blue Balls
      checkBlue.broadcastAndWait();
    }
    if(colour== 2){
      //Score Blue Balls and Drop Red Balls
      checkRed.broadcastAndWait();
    }
  }
}
