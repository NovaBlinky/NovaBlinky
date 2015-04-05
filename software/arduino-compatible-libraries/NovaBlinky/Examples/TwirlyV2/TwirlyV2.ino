#include <NovaBlinky.h>

// Nova Blinky LED test, version 2.0
// Modified from basic_twirly_exposed

//Define some constants:
//#define buttonA 5
//#define buttonB 4

//Create an instance of the NovaBlinky library:
NovaBlinky nb;

//Create a few globals:
boolean globalDir = true;
int globalCount = 0;
byte globalMode = 1;
byte multiplier = 4;
boolean ledState = false;
int count = 0;

//Setup some magic-value variables:
byte currLED_A;
byte currLED_B;
byte currLED_C;
byte currLED_D;

void setup() {
  nb.begin();  // setup blinky hardware
  resetVars(); // setup variables
  nb.updateLights(); // run first light update
}

// the loop routine runs over and over again forever:
void loop() {
  int b1=digitalRead(buttonA); int b2=digitalRead(buttonB);
  
  if(globalCount % (MaxLeds * 2) == 0) { globalDir = !globalDir; resetVars(); } // change direction every 2 cycles
  if(globalCount >= MaxLeds * multiplier) { globalDir = true; globalMode++; globalCount = 0; if(globalMode > 4) globalMode = 1; resetVars(); } // change functions every [multiplier] cycles
  
  if(globalMode == 1) runCustomBlinkyLoop1(globalDir); // run our custom function
  else if(globalMode == 2) runCustomBlinkyLoop2(globalDir); // here's an alternate function
  else if(globalMode == 3) runCustomBlinkyLoop3(globalDir); // here's another one
  else if(globalMode == 4) runCustomBlinkyLoop4(globalDir); // and another one
  
  // react to button presses:
  if(b1 == LOW && b2 == LOW) {
    multiplier++; eraseLightRing(false);
    // wait a while to make sure button was actually released:
    waitForButtonRelease(buttonA, 100);
    waitForButtonRelease(buttonB, 100);
    // flash light ring to indicate cycle multiplier has been increased:
    for(int i=0; i < multiplier-4; i++) {
      for(int i=0; i<MaxLeds; i++) digitalWrite(nb.pinMap[i],LOW);
      delay(500); eraseLightRing(false); delay(500);
    }
    nb.updateLights(); // revert light ring back to previous pattern
  } else if(b1 == LOW) {
    globalDir = true; globalCount = 0; globalMode--;
    if(globalMode < 1) globalMode = 4; eraseLightRing();
    // wait a while to make sure button was actually released:
    waitForButtonRelease(buttonA, 100); resetVars();
  } else if(b2 == LOW) {
    globalDir = true; globalCount = 0; globalMode++;
    if(globalMode > 4) globalMode = 1; eraseLightRing();
    // wait a while to make sure button was actually released:
    waitForButtonRelease(buttonB, 100); resetVars();
  }
  
  delay(80); // sets the speed
  globalCount++;
}

// custom function number 1:
void runCustomBlinkyLoop1(boolean direction) {
  nb.ledStates[currLED_A] = 0; /*nb.ledStates[currLED_B] = 0;*/ nb.ledStates[currLED_C] = 0; //nb.ledStates[currLED_D] = 0; // current LED gets turned on so it can be displayed
  nb.updateLights(); // update light ring
  nb.ledStates[currLED_A] = 1; /*nb.ledStates[currLED_B] = 1;*/ nb.ledStates[currLED_C] = 1; //nb.ledStates[currLED_D] = 1; // current LED gets turned off in preperaton for next loop
  
  // loop when last LED is reached:
  if(currLED_A == (direction ? (MaxLeds - 1) : 0)) currLED_A = direction ? 0 : (MaxLeds - 1);
  else currLED_A = currLED_A+(direction ? 1 : -1);
  //if(currLED_B == MaxLeds - 1) currLED_B = 0;
  //else currLED_B++;
  if(currLED_C == (direction ? (MaxLeds - 1) : 0)) currLED_C = direction ? 0 : (MaxLeds - 1);
  else currLED_C = currLED_C+(direction ? 1 : -1);
  //if(currLED_D == 0) currLED_D = MaxLeds - 1;
  //else currLED_D--;
}

// custom function number 2:
void runCustomBlinkyLoop2(boolean direction) {
  nb.ledStates[currLED_A] = (int)ledState; // current LED gets turned on
  
  // loop when last LED is reached:
  if(currLED_A == (direction ? (MaxLeds - 1) : 0)) currLED_A = direction ? 0 : (MaxLeds - 1);
  else currLED_A = currLED_A+(direction ? 1 : -1);
  
  nb.updateLights(); // update light ring
  count++; if(count == 12) { count = 0; ledState = !ledState; } //inverse colors for each loop
}

// custom function number 3:
void runCustomBlinkyLoop3(boolean direction) {
  if(direction) {
    if(currLED_A == MaxLeds-1) {
      // turn on all LEDs:
      for(int i=0; i<MaxLeds; i++) {
        nb.ledStates[i] = 0;
      }
      currLED_A = 0;
    } else {
      // turn off all LEDs:
      for(int i=0; i<MaxLeds; i++) {
        nb.ledStates[i] = 1;
      }
      currLED_A = MaxLeds-1;
    }
  } else {
    if(currLED_A == MaxLeds-1) {
      // turn on left-side LEDs:
      for(int i=0; i<MaxLeds; i++) {
        if(i > (MaxLeds/2)-1) nb.ledStates[i] = 0;
        else nb.ledStates[i] = 1;
      }
      currLED_A = 0;
    } else {
      // turn on right-side LEDs:
      for(int i=0; i<MaxLeds; i++) {
        if(i <= (MaxLeds/2)-1) nb.ledStates[i] = 0;
        else nb.ledStates[i] = 1;
      }
      currLED_A = MaxLeds-1;
    }
  }
  nb.updateLights();
}

// custom function number 4:
void runCustomBlinkyLoop4(boolean direction) {
  if(currLED_A == MaxLeds-1) currLED_B = currLED_A; // set B equal to A on start
  nb.ledStates[currLED_A] = 0; nb.ledStates[currLED_B] = 0; // next LED gets turned on so it can be displayed
  nb.updateLights(); // update light ring
  nb.ledStates[currLED_A] = 1; nb.ledStates[currLED_B] = 1; // current LED gets turned off in preperaton for next loop
  
  // loop when last LED is reached:
  if(currLED_A == (direction ? (MaxLeds - 1) : 0)) currLED_A = direction ? 0 : (MaxLeds - 1);
  else currLED_A = currLED_A+(direction ? 1 : -1);
  if(currLED_B == (direction ? 0 : (MaxLeds - 1))) currLED_B = direction ? (MaxLeds - 1) : 0;
  else currLED_B = currLED_B+(direction ? -1 : 1);
}

// turn off LEDs:
void eraseLightRing() {
  for(int i=0; i<MaxLeds; i++) nb.ledStates[i] = 1;
  nb.updateLights(); nb.setIndicatorLights(0);
} // another definition of the same function:
void eraseLightRing(boolean captureChange) {
  if(captureChange) { for(int i=0; i<MaxLeds; i++) nb.ledStates[i] = 1; nb.updateLights(); }
  else { for(int i=0; i<MaxLeds; i++) digitalWrite(nb.pinMap[i],HIGH); }
}

// turn off LEDs and reset the magic-value variables:
void resetVars() {
  // turn off LEDs, but don't run update:
  for(int i=0; i<MaxLeds; i++) { nb.ledStates[i] = 1; }
  // reset variables:
  currLED_A = (MaxLeds) - 1;
  currLED_B = (MaxLeds / 4 * 1) - 1;
  currLED_C = (MaxLeds / 4 * 2) - 1;
  currLED_D = (MaxLeds / 4 * 3) - 1;
  ledState = false; count = 0;
  nb.setIndicatorLights(globalMode-1);
}

// wait for a button to be released for an amount of time:
void waitForButtonRelease(byte pinNum, unsigned int time) {
  unsigned int bCount = 0;
  while(bCount < time) {
    delay(1); bCount++;
    if(digitalRead(pinNum) == LOW) bCount = 0;
  }
}
