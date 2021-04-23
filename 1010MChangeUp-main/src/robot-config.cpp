#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotorF = motor(PORT15, ratio18_1, false);
motor RightMotorB = motor(PORT13, ratio18_1, true);
motor RightMotorF = motor(PORT12, ratio18_1, true);
motor LeftMotorB = motor(PORT14, ratio18_1, false);
controller Controller1 = controller(primary);
motor IntakeR = motor(PORT6, ratio18_1, true);
motor IntakeL = motor(PORT7, ratio18_1, false);
motor Elevator2 = motor(PORT20, ratio6_1, false);
motor Elevator = motor(PORT10, ratio6_1, false);
inertial Inertial17 = inertial(PORT16);
/*vex-vision-config:begin*/
signature Vision19__REDBALL = signature (1, 6833, 9485, 8159, -619, 77, -271, 2.5, 0);
signature Vision19__BLUEBALL = signature (2, -2731, -1927, -2329, 7117, 12463, 9790, 0.7, 0);
signature Vision19__HUMAN = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision19 = vision (PORT19, 50, Vision19__REDBALL, Vision19__BLUEBALL, Vision19__HUMAN);
/*vex-vision-config:end*/
controller Controller2 = controller(partner);

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