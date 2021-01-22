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
extern inertial Inertial17;
extern signature Vision10__REDBALL;
extern signature Vision10__BLUEBALL;
extern signature Vision10__HUMAN;
extern signature Vision10__SIG_4;
extern signature Vision10__SIG_5;
extern signature Vision10__SIG_6;
extern signature Vision10__SIG_7;
extern vision Vision10;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );