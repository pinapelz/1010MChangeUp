#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotorF = motor(PORT17, ratio18_1, false);
motor RightMotorB = motor(PORT11, ratio18_1, true);
motor RightMotorF = motor(PORT12, ratio18_1, true);
motor LeftMotorB = motor(PORT18, ratio18_1, false);
controller Controller1 = controller(primary);
motor IntakeR = motor(PORT1, ratio18_1, true);
motor IntakeL = motor(PORT9, ratio18_1, false);
motor Elevator2 = motor(PORT10, ratio6_1, true);
motor Elevator = motor(PORT20, ratio6_1, true);
inertial Inertial19 = inertial(PORT19);
/*vex-vision-config:begin*/
signature Vision4__REDBALL = signature (1, 6833, 9485, 8159, -619, 77, -271, 2.5, 0);
signature Vision4__BLUEBALL = signature (2, -2731, -1927, -2329, 7117, 12463, 9790, 0.7, 0);
signature Vision4__HUMAN = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision4 = vision (PORT4, 50, Vision4__REDBALL, Vision4__BLUEBALL, Vision4__HUMAN);
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