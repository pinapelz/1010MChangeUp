#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotorF = motor(PORT5, ratio18_1, false);
motor LeftMotorB = motor(PORT2, ratio18_1, false);
motor RightMotorF = motor(PORT3, ratio18_1, true);
motor RightMotorB = motor(PORT4, ratio18_1, true);
controller Controller1 = controller(primary);
motor IntakeR = motor(PORT21, ratio18_1, false);
motor Elevator = motor(PORT1, ratio18_1, false);
motor Elevator2 = motor(PORT6, ratio18_1, true);
motor IntakeL = motor(PORT7, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}