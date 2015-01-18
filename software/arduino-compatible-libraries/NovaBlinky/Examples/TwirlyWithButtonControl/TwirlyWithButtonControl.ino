#include <NovaBlinky.h>
//Added Button Support and Speed Control (Scott Bennett, 1/17/15)

// basic blinky led test

NovaBlinky nb;
const int button1=4;
const int button2=5;
void nova_blinky_customized_blinky_loop(void);
int max=100;
int speed=50;

void setup() {
    nb.setup();  // setup blinky hardware
    nb.cur_led = nb.max_leds - 1;
    pinMode(button1,INPUT);
    digitalWrite(button1,HIGH); //turn on pullup
    pinMode(button2,INPUT);
    digitalWrite(button2,HIGH); //turn on pullup
}

// the loop routine runs over and over again forever:
void loop() {
   nova_blinky_customized_blinky_loop(); // call our own counter-clockwise
   delay(max-abs(speed)); // sets the speed
   int b1=digitalRead(button1);
   int b2=digitalRead(button2);
   if (b2==LOW) {
     if (speed>(-1*max)) speed=speed-1;
   } else if (b1==LOW) {
     if (speed<max) speed=speed+1;
   }
}

void nova_blinky_customized_blinky_loop()
{
   for(int i=0;i<nb.max_leds;i++) nb.led_states[i]=1; //all off
   if (speed>0) {
     nb.cur_led=nb.cur_led+1;
     if (nb.cur_led==nb.max_leds) nb.cur_led=0;
   } else if (speed<0) {
     if (nb.cur_led==0) {
       nb.cur_led=nb.max_leds-1;
     } else {
       nb.cur_led=nb.cur_led-1;
     }
   }
   nb.led_states[nb.cur_led]=0;
   for (int i=0; i<nb.max_leds; i++)   // update state of all leds
   {
     digitalWrite(nb.led_to_pin_map[i],nb.led_states[i]);
   }
}

