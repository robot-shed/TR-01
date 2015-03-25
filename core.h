// core.h

#include "Motor.h"

// externals

// motors  
// This is so if a user routine wanted to do someting cutom with a motor, it should not requrie
// a change to core.cpp.  In general however motor access should be thorugh core.cpp functions.

extern DCMotor left;
extern DCMotor right;

// prototypes for core routines

void initilize();         // setup the motors
void forward();           // go forward
void reverse();           // go backwards
void turnLeftZero();      // zero radius trun left
void turnRightZero();     // zero radius trun right
void turnLeft();          // wide trun left
void turnRight();         // wide turn right
void stop();              // turn off the motor
void setSpeed(int);       // set the speed for both motors.  NOTE: does not engage the motors, or change the current speed.
void applySpeed();        // change the speed of both motors to current setting.
void changeSpeed(int);    // change the speed of both motors by a delta
