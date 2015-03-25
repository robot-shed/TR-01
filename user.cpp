// user.cpp

// This file contains routines that typiclay are modifed for a specific experiment for TR-01. 

#include "ir.h"
#include "core.h"
#include "user.h"
#include "notes.h"

// Globals

// actions
int action = READY;
int nextAction;
unsigned long delayTime;
unsigned long previousMillis;

// Private functions

// mapCommand - map commands from a specific IR remote to generic commands
// Some commands are a two command sequence, we ignore the first command and
// map the second command.
int mapCommand(int irCommand, int irDevice)
{
  int command = IGNORE;
  
  switch(irCommand)
  {
    case irPresetPlus :            // Stop
      command = STOP;
      break;
    case irPresetMinus :           // Reverse
      command = REVERSE;
      break;
    case irVolumePlus :            // Right
      command = RIGHT;
      break;
    case irVolumeMinus :           // Decelerate
      command = DECELERATE;
      break;
    case irMuting :                // unused
      break;
    case irPower :                 // unused
      break;
    case irTapePauseA :            // unused
      break;
    case irPhono :                 // * ignore
      break;
    case irTuner :                 // Left
      command = LEFT;
      break;
    case irVideo :                 // Default
      command = STANDARD;
      break;
    case irTape :                  // ignore
      break;
    case irCD :                    // ignore
      break;
    case irPhonoStart :            // unused
      break;
    case irPhonoStop :             // unused
      break;
    case irDBFB :                  // * DBFB = 12 (unused); CD next track = 17 (accelerate)
      if (irDevice == 17)
      {
        command = ACCELERATE;
      }
      break;
    case irCDPlay :                // * CD Play = 17 (Max**); Tape Play A = 16 (unused)
      if (irDevice == 17)
      {
        command = MAX;
      }
      break;
    case irRewindA :               // unused
      break;
    case irFastForwardA :          // unused
      break;
    case irRecordA :               // unused
      break;
    case irReversePlayA :          // unused
      break;
    case irTapeStopA :             // * Tape Stop A = 16 (unused); CD Stop = 17 (forward)
      if (irDevice == 17)
      {
        command = FORWARD;
      }
      break;
    case irTape2 :                 // ignore
      break;
    case irDiscSkip :              // Jaunty tune
      break;
    default :
      break;
  }
  
  return command;
}

// setDelay - convience routine to set up a delay
void setDelay(unsigned long delta, int next)
{
  delayTime = delta;
  nextAction = next;
  action = DELAY;
  previousMillis = millis();
}

// Public functions

// doCommand - execute whatever command was recived by the IR remote
void doCommand(int irCommand, int irDevice)
{ 
  int command = mapCommand(irCommand, irDevice);  // map from the specific IR remote to generic commands
#ifdef DEBUG
  Serial.print("Command :");
  Serial.println(command, DEC);
#endif
  switch(command)
  { case FORWARD :
      forward();
      break;
    case REVERSE :
      reverse();
      break;
    case LEFT :
      turnLeftZero();
      break;
    case RIGHT :
      turnRightZero();
      break;
    case STOP : 
      stop();
      break;
    case STANDARD : 
      setSpeed(defaultSpeed);  
      break;
    case MAX :
      setSpeed(100);   
      break;      
    case ACCELERATE :
      changeSpeed(speedDelta);
      break;
    case DECELERATE :
      changeSpeed(-speedDelta);
      break;
    case IGNORE :
      break;
    default :
      stop();
      break;
  }
}

// doAction - 
void doAction()
{
  unsigned long currentMillis;
  switch(action)
  {
    case DELAY :
      currentMillis = millis();
       if (currentMillis - previousMillis >= delayTime)
       {
          action = nextAction;
       }
       break;
    case READY :
    default :
      break;  
   }
}

