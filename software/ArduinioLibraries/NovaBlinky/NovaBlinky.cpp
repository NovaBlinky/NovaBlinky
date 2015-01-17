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

const unsigned char NovaBlinky::max_leds = 12; // number of leds around the face

const unsigned char NovaBlinky::led_to_pin_map[] =
{23,22,21,20,19,18,8,9,10,11,6,7};

unsigned char NovaBlinky::cur_led = 0;
unsigned char NovaBlinky::led_states[] = {1,1,1,1,1,1,1,1,1,1,1,1};

void NovaBlinky::setup(void)
{
  // call once to initialize Blinky hardware
  int i;
  for (i=0; i<max_leds; i++)
  {
    pinMode(led_to_pin_map[i],OUTPUT); // program pins for output
  }
}

void NovaBlinky::basic_blinky_loop(void)
{
  // traditionally called from loop(), do things that regularly need to be done
  // on Blinky
  led_states[cur_led] = 1; // curled gets turned off

  if (++cur_led >= max_leds) // reset current led on wrap
    cur_led = 0;

  led_states[cur_led] = 0; // next led gets turned on

  int i;

  for (i=0; i<max_leds; i++)   // update state of all leds
  {
    digitalWrite(led_to_pin_map[i],led_states[i]);
  }
}
