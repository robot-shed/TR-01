// TR-01

// Main file for TR-01.  This file contains the setup, and loop functions, and any ISR's.  In general this
// file should not need to be modified for a spcific experiment.

// includes

#include "core.h"
#include "user.h"

// defining DEBUG will cause diagnostics to be sent out the serial line.
//#define DEBUG

// Constants

const int runPin = 3;            // pin for run/program switch
const int speakerPin = 4;        // pin for speaker (really just a placeholder in this file)

// IR
const int irPin = 2;             // this must be an external interrupt pin
const int interrupt = 0;         // external interrupt #.  This must match irPin.
const int irDelay = 200;         // delay to "skip over" repeated IR commands

// Constants for Sony IR remote
const unsigned long oneWidth = 800ul;     // logic 1 typically 1200uS
const unsigned long startWidth = 1800ul;  // start bit typically 2400uS
const int commandBits = 7;       // number of bits of the command portion of signal
const int deviceBits = 5;        // number of bits of the device portion of signal
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
// Globals

// IR
volatile byte irReady;           // global variable to signal IR data avaliable.
volatile byte irCommand;         // global variable used to store IR Command.
volatile byte irDevice;          // global variable used to store IR Device.

// setup - initilize the Arduino
void setup() 
{
  // intilize pins      
  pinMode(runPin, INPUT);
  // intilize motors
  initilize();
  setSpeed(defaultSpeed);
  // call IRdecode when IRpin changes state  
  attachInterrupt(interrupt, IRdecode, CHANGE);        
  
#ifdef DEBUG
  Serial.begin(115200);                      // initialize USB serial port for serial monitor on PC
  Serial.println("TR-01 DEBUG");
#endif 
}

// loop - main processing loop
void loop()
{
  int runState = digitalRead(runPin); 
  
  // if runState is high (swich is on) run the robot program otherwise 
  // do nothing (allow for programming).
  if (runState == HIGH) 
  {       
// process a remote command if there is one
    if (irReady != 0)
    {
#ifdef DEBUG
      Serial.print("IRCommand :");
      Serial.print(irCommand, DEC);     // display received command
      Serial.print(" Device :");
      Serial.println(irDevice, DEC);    // display recived device
#endif      
      doCommand(irCommand, irDevice); // execute whatever command has been recieved.
      delay(irDelay);                 // most remotes will repeat signal 2 or 3 times, use this delay to prevent repetition of command                           
      irReady = 0;                    // reset irReady until new command received
    }
    doAction();
  }
  else
  {
    stop();
  }
}

// IR routines

// IRDecode - Sony IR Code (SIRC) Decoder. 
// As set up this handles 12 bit codes (7 bits command, 5 bits device)
void IRdecode()
{
  volatile static unsigned long irBitWidth;  // width of data bit in uS
  volatile static byte irData;               // temporary storage of byte value as bits are read
  volatile static byte irBitValue;           // decimal value of bit being read (1,2,4,8,16,32,64,128)
  volatile static byte irBitCount;           // counts number of bits since start bit  

  if (digitalRead(irPin) == 0)               // check state of IR receiver output 
  {
    irBitWidth = micros();                   // bit starts when IR receiver pin goes low
  }
  else                                       // IR receiver output high - end of bit
  {
    irBitWidth = micros() - irBitWidth;      // measure width of bit
    if(irBitWidth > oneWidth)                // bitwidth > 800uS = logic "1" (logic 1 typically 1200uS)
    {
      irData += irBitValue;                  // increment data by bit value
    }
    irBitValue *= 2;                         // bitvalue updated for next bit (1,2,4,8,16,32,64,128)
    irBitCount++;                            // count the bits


    if(irBitCount == commandBits)            // if we have all the command portion, save it.
    {
      irBitValue = 1;                        // reset bit value for device portion of singal
      irCommand = irData;                    // make command available to user
      irData = 0;                            // reset data for device portion of signal
    }
    if(irBitCount == commandBits + deviceBits)  // if we have the device portion, save it.
    {
      irBitValue = 0;                       // additional bits have a value of 0
      irDevice = irData;                    // make device available to user
      irReady = 1;                          // signal data ready;
    }

    if(irBitWidth > startWidth)              // start bit resets decoder values (start bit typically 2400uS)
    {
      irBitValue = 1;
      irBitCount = 0;
      irData = 0;
      irCommand = 0;
      irDevice = 0;
    }  
  }
}
