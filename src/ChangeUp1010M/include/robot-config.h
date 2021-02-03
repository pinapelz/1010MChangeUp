using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftMotorF;
extern motor LeftMotorB;
extern motor RightMotorF;
extern motor RightMotorB;
extern controller Controller1;
extern motor IntakeR;
extern motor IntakeL;
extern motor Elevator2;
extern motor Elevator;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );