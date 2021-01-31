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
void hasBlueCallback() {

  Vision10.takeSnapshot(Vision10__BLUEBALL); //Check for a blue ball
  if (Vision10.objectCount > 0) { //If there are more than one blue objects detected
      IntakeL.stop();
      IntakeR.stop();
      releaseBall(500,3); //Drop the ball by a preset amount (3 rotations in 500 ms)
      ballsProcessed++; //Increase balls processed
    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__REDBALL); //Check for a red ball

  if (Vision10.objectCount > 0) { //If there are more than oen red blue objects detected
          IntakeL.stop();
      IntakeR.stop();
      elevatorScore(800,5); //Score the ball by a preset amount (800,5)
      ballsProcessed++; //Increase the balls processed
  }

  IntakeL.spin(fwd, 100, pct); //Intake until the balls are in he intake
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();

}








void hasRedCallback() {
  Vision10.takeSnapshot(Vision10__REDBALL); //Check for a red ball
  if (Vision10.objectCount > 0) { //If there are more than one red balls
      IntakeL.stop();
      IntakeR.stop();
      releaseBall(500,3); //Drop the red ball through the back
      ballsProcessed++; //Increase the number of balls processed
    Elevator2.stop();
  }

  Vision10.takeSnapshot(Vision10__BLUEBALL); //Check for blue balsl

  if (Vision10.objectCount > 0) { //If there are more than one blue balls detected
          IntakeL.stop();
      IntakeR.stop();
      elevatorScore(800,5); //Score the red ball by a preset amount (5 revolutions in 800 ms)
      ballsProcessed++; //Increase the number of balls processed
  }

  IntakeL.spin(fwd, 100, pct); //Intake until the next ball is detected
  IntakeR.spin(fwd, 100, pct);
  Elevator2.stop();

}



void sortBall(int process, int colour) { //Sorting ball function
  ballsProcessed = 0;
  event checkBlue = event();
  event checkRed = event();
  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  while (process!=ballsProcessed) { //While not all of the balls are sorted
    if(ballsProcessed==10){ //Set the ball sorted to 10 to cancel the sorting
      stopAll(); //Stop all the motors
      break;
    }
    if(Controller2.ButtonUp.pressing()){ //Emergency stop sorting
      ballsProcessed = 10;
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
