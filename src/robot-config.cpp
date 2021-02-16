#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotorF = motor(PORT15, ratio18_1, false);
motor RightMotorB = motor(PORT3, ratio18_1, true);
motor RightMotorF = motor(PORT12, ratio18_1, true);
motor LeftMotorB = motor(PORT5, ratio18_1, false);
controller Controller1 = controller(primary);
motor IntakeR = motor(PORT6, ratio18_1, true);
motor IntakeL = motor(PORT7, ratio18_1, false);
motor Elevator2 = motor(PORT19, ratio6_1, false);
motor Elevator = motor(PORT20, ratio6_1, true);
inertial Inertial17 = inertial(PORT17);
/*vex-vision-config:begin*/
signature Vision10__REDBALL = signature (1, 6833, 9485, 8159, -619, 77, -271, 2.5, 0);
signature Vision10__BLUEBALL = signature (2, -2731, -1927, -2329, 7117, 12463, 9790, 0.7, 0);
signature Vision10__HUMAN = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision10 = vision (PORT10, 50, Vision10__REDBALL, Vision10__BLUEBALL, Vision10__HUMAN);
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