// user.h

#include <arduino.h>   // included to get arduino data type definitions

// Constants

// commands
const int IGNORE = 0;
const int STOP = 1;
const int REVERSE = 2;
const int RIGHT = 3;
const int DECELERATE = 4;
const int LEFT = 5;
const int STANDARD = 6;
const int ACCELERATE = 7;
const int MAX = 8;
const int FORWARD = 9;

// actions
const int READY = 0;
const int DELAY = 1;

// Motor
const byte defaultSpeed = 70;    // 70% is starting speed.
const byte speedDelta = 5;       // 5% change in speed.

// prototyopes for public functions in user.cpp

void doCommand(int, int);        // execute IR remote command
void doAction();                 // 
