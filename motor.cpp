// Motor.cpp

// members functions to implement the DCMotor class

#include "Motor.h"

// init - initilize the motor
void DCMotor::init(byte ID)
{
  motorID = ID;
  if (motorID == leftMotor)
  {
    interfacePin1 = pinI3;
    interfacePin2 = pinI4;
    pwmPin = speedPinB;

  }
  else
  {
    interfacePin1 = pinI1;
    interfacePin2 = pinI2;
    pwmPin = speedPinA;
  }
  pinMode(interfacePin1, OUTPUT);
  pinMode(interfacePin2, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  stop();
}

// setSpeed - set the speed of the moter as a percentage from 0 to 100.
// 0 will stop the motor, 1 will be the minimum speed for the motor.
void DCMotor::setSpeed(int s)
{
  if (s > 100)
  {
    s = 100;
  }
  if (s < 0)
  {
    s = 0;
  }
  if (s == 0)
  {
    speed = 0;
  }
  else
  {
    speed = map(s, 1, 100, minSpeed, maxSpeed);
  }
}

// getSpeed - return the current motor speed
int DCMotor::getSpeed()
{
  if (speed == 0)
  {
    return 0;
  }
  else
  {
    return map(speed, minSpeed, maxSpeed, 1, 100);
  }
}

// getRawSpeed - return the PWM value for the motor, for dubugging.
int DCMotor::getRawSpeed()
{
  return speed;
}

// applySpeed - take the speed value and acutaly change the motor speed.
void DCMotor::applySpeed()
{
  analogWrite(pwmPin, speed);
}

// forward - make the motor rotate "forward"
void DCMotor::forward()
{
  if (motorID == leftMotor) //turn DC Motor B counter clockwise
  {
    analogWrite(pwmPin, speed);
    digitalWrite(interfacePin1, HIGH);
    digitalWrite(interfacePin2, LOW);
  }
  else //turn DC Motor A clockwise
  {
    analogWrite(pwmPin, speed);
    digitalWrite(interfacePin1, LOW);
    digitalWrite(interfacePin2, HIGH);
  }
}

// reverse - make the motor rotate "backwards"
void DCMotor::reverse()
{
  if (motorID == leftMotor) //turn DC Motor B clockwise
  {
    analogWrite(pwmPin, speed);
    digitalWrite(interfacePin1, LOW);
    digitalWrite(interfacePin2, HIGH);
  }
  else //turn DC Motor A counter clockwise
  {
    analogWrite(pwmPin, speed);
    digitalWrite(interfacePin1, HIGH);
    digitalWrite(interfacePin2, LOW);
  }
}

// stop - stop the motor.  Do this by unenableing the pwm pin.  This should
// be done to avoid damaging the motor.
void DCMotor::stop()
{
  digitalWrite(pwmPin, LOW);
}
