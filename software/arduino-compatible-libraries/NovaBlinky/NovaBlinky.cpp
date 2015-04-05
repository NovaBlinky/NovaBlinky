/*
  NovaBlinky.cpp

  Basic Library Functions for NovaBlinky - an Arduino Leonardo-compatible,
  ATMega 32u4-based board

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 */

#include "NovaBlinky.h"
#include "Arduino.h"

// this part seems a little repetitive...
//const unsigned char NovaBlinky::maxLeds = MaxLeds; // number of leds around the face

const unsigned char NovaBlinky::pinMap[] =
{23,22,21,20,19,18,8,9,10,11,6,7}; // relation between led numbers and pin numbers

unsigned char NovaBlinky::ledStates[] = {1,1,1,1,1,1,1,1,1,1,1,1};

// call once to initialize Blinky hardware:
void NovaBlinky::begin(void)
{
  for(int i=0; i<MaxLeds; i++) {
    pinMode(pinMap[i], OUTPUT); // program pin for output
    digitalWrite(pinMap[i], HIGH); // turn off led
  }
  pinMode(buttonA, INPUT); pinMode(buttonB, INPUT); //configure button pin-modes
  digitalWrite(buttonA, HIGH); digitalWrite(buttonB, HIGH); //enable button pullups
}

// run an LED update based on the contents of ledStates:
void NovaBlinky::updateLights(void)
{
  for(int i=0; i<MaxLeds; i++) { // loop though all LED pins
    digitalWrite(pinMap[i], ledStates[i]); // set LED to value saved in ledStates table
  }
}

// turn all lights on or off:
void NovaBlinky::setLights(boolean onOff)
{
  setLights(onOff, true, false);
}
void NovaBlinky::setLights(boolean onOff, boolean captureChange)
{
  setLights(onOff, captureChange, false);
}
void NovaBlinky::setLights(boolean onOff, boolean captureChange, boolean skipUpdate)
{
    if(captureChange) {
        for(int i=0; i<MaxLeds; i++) ledStates[i] = !onOff;
        setIndicatorLights(0); if(!skipUpdate) updateLights();
    } else if(!skipUpdate) {
        for(int i=0; i<MaxLeds; i++) digitalWrite(pinMap[i], !onOff);
    }
}

// control the board's RX and TX lights: (this little hack only works on the Arduino Leonardo)
void NovaBlinky::setIndicatorLights(byte status)
{
  if(status == 1) { RXLED1; TXLED0; }
  else if(status == 2) { RXLED0; TXLED1; }
  else if(status == 3) { RXLED1; TXLED1; }
  else { RXLED0; TXLED0; }
}

// call periodically in loop() to create a light-casing pattern:
void NovaBlinky::basicBlinkyLoop(void)
{
  basicBlinkyLoop(true);
}
void NovaBlinky::basicBlinkyLoop(boolean dir)
{
  ledStates[_curled] = 0; // currled gets turned on so it can be displayed
  updateLights(); // update light ring
  ledStates[_curled] = 1; // currled gets turned off in preperaton for next loop
  
  // loop when last led is reached:
  if(_curled == (dir ? (MaxLeds - 1) : 0)) _curled = dir ? 0 : (MaxLeds - 1);
  else _curled = _curled + (dir ? 1 : -1);
}
