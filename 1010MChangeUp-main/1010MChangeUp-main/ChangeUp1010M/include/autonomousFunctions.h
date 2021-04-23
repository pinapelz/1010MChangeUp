#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void resetEncoders() {
  LeftMotorF.resetPosition();
  LeftMotorB.resetPosition();
  RightMotorF.resetPosition();
  RightMotorB.resetPosition();
}
