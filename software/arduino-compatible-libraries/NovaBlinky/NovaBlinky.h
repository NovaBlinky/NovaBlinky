/*
 NovaBlinky Library Functions

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

#ifndef NovaBlinky_h
#define NovaBlinky_h

#include "Arduino.h"

#define BLINKY_NUMBER_OF_LEDS 12

class NovaBlinky
{
  public:
    void setup(void);
    void basic_blinky_loop(void);
    static const unsigned char max_leds;
    static const unsigned char led_to_pin_map[BLINKY_NUMBER_OF_LEDS] ;
    static unsigned char cur_led;
    static unsigned char led_states[BLINKY_NUMBER_OF_LEDS];
};

#endif // NovaBlinky_h
