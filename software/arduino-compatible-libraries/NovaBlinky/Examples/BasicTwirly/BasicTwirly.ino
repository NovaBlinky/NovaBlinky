#include <NovaBlinky.h>

// basic blinky led test

NovaBlinky nb;

void setup() {        
  nb.begin();  // setup blinky hardware
}

// the loop routine runs over and over again forever:
void loop() {
  nb.basicBlinkyLoop(); // call basic clockwise twirly loop
  delay(45); // sets the speed
}
