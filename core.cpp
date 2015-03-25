// core.cpp

// This file contains routines that provide basic (core) functionality for TR-01.  In gneral
// these routines will just be used, and not modified.

#include "core.h"

// defining DEBUG will cause diagnostics to be sent out the serial line.
//#define DEBUG

// Constatns

const int speakerPin = 4;       // pin for speaker

// Globals

// Motor
DCMotor left;                   // left motor
DCMotor right;                  // right motor

// public functions

// initilize - setup both motors
void initilize()
{
  left.init(leftMotor);
  right.init(rightMotor);
}

// forward - go forward
void forward()
{
  left.forward();
  right.forward();
}

// reverse - go backwards
void reverse()
{
  left.reverse();
  right.reverse();
}

// turnLeftZero - zero radius trun left
void turnLeftZero()
{
  left.reverse();
  right.forward();
}

// turnRightZero - zero radius trun right
void turnRightZero()
{
  left.forward();
  right.reverse();
}

// turnLeft - do a wide turn left
void turnLeft()
{
  left.setSpeed(1);
  right.setSpeed(100);
  left.forward();
  right.forward();
}

// turnRight - do a wide turn right
void turnRight()
{
  left.setSpeed(100);
  right.setSpeed(1);
  left.forward();
  right.forward();
}

// stop - turn off the motors
void stop()
{
  left.stop();
  right.stop();
}

// setSpeed - set the speed for both motors.
// NOTE: this sets the speed for the next motor command (forward, etc.). It does not 
// engage the motors, or change the current speed.
void setSpeed(int s)
{
  left.setSpeed(s);
  right.setSpeed(s);
#ifdef DEBUG
  Serial.print("Left PWM :");
  Serial.print(left.getRawSpeed(), DEC);
  Serial.print(" Right PWM :");
  Serial.println(right.getRawSpeed(), DEC);
#endif
}

// applySpeed - change the speed of both motors to current setting.
void applySpeed()
{
  left.applySpeed();
  right.applySpeed();
}

// changeSpeed - change the speed of both motors by a delta
void changeSpeed(int delta)
{
  left.setSpeed(left.getSpeed() + delta);
  right.setSpeed(right.getSpeed() + delta);
  applySpeed();
#ifdef DEBUG
  Serial.print("Left PWM :");
  Serial.print(left.getRawSpeed(), DEC);
  Serial.print(" Right PWM :");
  Serial.println(right.getRawSpeed(), DEC);
#endif
}

void playNote(int note, int duration)
{
  tone(speakerPin, note, duration);
}
