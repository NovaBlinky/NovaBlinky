#include <NovaBlinky.h>
//Added Button Support and Speed Control (Scott Bennett, 1/17/15)

// basic blinky led test

NovaBlinky nb;

byte curr_led = MaxLeds - 1;
int max=100;
int speed=50;

void setup() {
    nb.begin();  // setup blinky hardware
}

// the loop routine runs over and over again forever:
void loop() {
   nova_blinky_customized_blinky_loop(); // call our own counter-clockwise
   delay(max-abs(speed)); // sets the speed
   int b1=digitalRead(buttonA);
   int b2=digitalRead(buttonB);
   if (b1==LOW) {
     if (speed>(-1*max)) speed=speed-1;
   } else if (b2==LOW) {
     if (speed<max) speed=speed+1;
   }
}

void nova_blinky_customized_blinky_loop() {
   for(int i=0; i<MaxLeds; i++) nb.ledStates[i]=1; //all off
   if (speed>0) {
     curr_led++;
     if (curr_led==MaxLeds) curr_led=0;
   } else if (speed<0) {
     if (curr_led==0) {
       curr_led=MaxLeds-1;
     } else {
       curr_led--;
     }
   }
   nb.ledStates[curr_led]=0;
   for(int i=0; i<MaxLeds; i++) { // update state of all leds
    digitalWrite(nb.pinMap[i], nb.ledStates[i]);
  }
}
