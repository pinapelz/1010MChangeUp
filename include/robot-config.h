using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor LeftMotorF;
extern motor RightMotorB;
extern motor RightMotorF;
extern motor LeftMotorB;
extern controller Controller1;
extern motor IntakeR;
extern motor IntakeL;
extern motor Elevator2;
extern motor Elevator;
extern inertial Inertial19;
extern signature Vision4__REDBALL;
extern signature Vision4__BLUEBALL;
extern signature Vision4__HUMAN;
extern signature Vision4__SIG_4;
extern signature Vision4__SIG_5;
extern signature Vision4__SIG_6;
extern signature Vision4__SIG_7;
extern vision Vision4;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );