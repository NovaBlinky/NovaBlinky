#include <NovaBlinky.h>

// basic blinky led test

byte curr_led;

NovaBlinky nb;

void setup() {        
   nb.begin();  // setup blinky hardware
   curr_led = MaxLeds - 1;
}

// the loop routine runs over and over again forever:
void loop() {
  nova_blinky_customized_blinky_loop(); // call our own counter-clockwise
  delay(45); // sets the speed
}

void nova_blinky_customized_blinky_loop() {
  // traditionally called from loop(), do things that regularly need to be done
  // modified from basic_blinky_loop to go counter clockwise
  nb.ledStates[curr_led] = 1; // curled gets turned off
  
  if(!(curr_led--)) curr_led = MaxLeds - 1; // reset current led on wrap
  
  nb.ledStates[curr_led] = 0; // next led gets turned on
  
  int i;
  for(i=0; i<MaxLeds; i++) { // update state of all leds
    digitalWrite(nb.pinMap[i], nb.ledStates[i]);
  }
}
