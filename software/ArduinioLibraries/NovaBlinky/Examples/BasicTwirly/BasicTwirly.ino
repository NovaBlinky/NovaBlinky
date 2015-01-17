#include <NovaBlinky.h>

// basic blinky led test

NovaBlinky nb;

void setup() {        
   nb.setup();  // setup blinky hardware
}

// the loop routine runs over and over again forever:
void loop() {
  nb.basic_blinky_loop(); // call basic clockwise twirly loop
  delay(10); // sets the speed

}
