/*
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
    double LateralmotorPower = (error * kP + totalError * kI + derivative * kD);
// Add values up

    int turnDifference = LeftMotorF.position(deg) - RightMotorF.position(deg);
// Encoder Position int terror = ttarget - turnDifference; int tderivative =
terror - tpreviousError;
    // ttotalError += terror; //Integral take it out if not needed
    double turnMotorPower = (terror * tkP + ttotalError * tkI + tderivative *
tkD); if (intakeBool == true) {
      //redundant but won't work without it
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower,
voltageUnits::volt); // Run the voltage LeftMotorB.spin(directionType::fwd,
LateralmotorPower + turnMotorPower, voltageUnits::volt);
      RightMotorF.spin(directionType::fwd, LateralmotorPower -
turnMotorPower,voltageUnits::volt); RightMotorB.spin(directionType::fwd,
LateralmotorPower - turnMotorPower,voltageUnits::volt); if (LateralmotorPower
< 1.0 || turnMotorPower < 1.0) { Elevator.stop(hold); Elevator2.stop(hold);
        IntakeL.stop(vex::brakeType::coast);
        IntakeR.stop(coast);
      }
      IntakeL.spin(forward, 100, pct);
      IntakeR.spin(forward, 100, pct);
      Elevator.spin(forward, kintakespeed, pct);
      Elevator2.spin(forward, kintakespeed, pct);
    } else if (intakeBool == false) {
      LeftMotorF.spin(directionType::fwd, LateralmotorPower + turnMotorPower,
voltageUnits::volt); LeftMotorB.spin(directionType::fwd, LateralmotorPower +
turnMotorPower, voltageUnits::volt); RightMotorF.spin(directionType::fwd,
LateralmotorPower - turnMotorPower, voltageUnits::volt);
      RightMotorB.spin(directionType::fwd, LateralmotorPower - turnMotorPower,
voltageUnits::volt); Elevator.stop(hold); Elevator2.stop(brakeType::hold);
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

*/