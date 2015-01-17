#include <NovaBlinky.h>

// basic blinky led test

NovaBlinky nb;

void nova_blinky_customized_blinky_loop(void);

void setup() {        
   nb.setup();  // setup blinky hardware
   nb.cur_led = nb.max_leds - 1;
}

// the loop routine runs over and over again forever:
void loop() {
  nova_blinky_customized_blinky_loop(); // call our own counter-clockwise
  delay(10); // sets the speed

}

void nova_blinky_customized_blinky_loop()
{
  // traditionally called from loop(), do things that regularly need to be done
  // modified from basic_blinky_loop to go counter clockwise
  nb.led_states[nb.cur_led] = 1; // curled gets turned off

  if (!(nb.cur_led--)) // reset current led on wrap
    nb.cur_led = nb.max_leds - 1;

  nb.led_states[nb.cur_led] = 0; // next led gets turned on

  int i;

  for (i=0; i<nb.max_leds; i++)   // update state of all leds
  {
    digitalWrite(nb.led_to_pin_map[i],nb.led_states[i]);
  }
}
