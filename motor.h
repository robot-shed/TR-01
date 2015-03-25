// motor.h

// class definition for DCMotor

#include <Arduino.h>   // included to get arduino data types

// Seed Studio Motor Shield V2.1
const byte pinI1 = 8;             // define I1 interface (motor A) (right)
const byte pinI2 = 11;            // define I2 interface (motor A)
const byte speedPinA = 9;         // enable motor A
const byte pinI3 = 12;            // define I3 interface (motor B) (left)
const byte pinI4 = 13;            // define I4 interface (motor B)
const byte speedPinB = 10;        // enable motor B

const byte maxSpeed = 255;        // max motor speed
const byte minSpeed = 140;        // minimum motor speed (below this they tend to stall)

// motor ID
const byte leftMotor  = 0;        // Motor B on the shield
const byte rightMotor = 1;        // Motor A on the shield

class DCMotor
{
  byte motorID;             // identify which motor this is
  byte interfacePin1;       // first interface pin
  byte interfacePin2;       // second interface pin
  byte pwmPin;              // speed pin
  int speed;                // current motor speed as PWM value
public:
  void init(byte motorID);  // initilize the motor
  void setSpeed(int s);     // set the speed of the moter as a percentage from 0 to 100.
  int getSpeed();           // return the current motor speed
  int getRawSpeed();        // return the PWM motor speed. for deubgging purposes only.
  void applySpeed();        // update the motor speed.
  void forward();           // make the motor rotate "forwards"
  void reverse();           // make the motor rotate "backwards"
  void stop();              // stop the motor
};
