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

#define MaxLeds 12 // number of leds around the face

#define buttonA 5 // pin number of left button
#define buttonB 4 // pin number of right button

class NovaBlinky
{
  public:
    void begin(void);
    void basicBlinkyLoop(void);
    void basicBlinkyLoop(boolean);
    void setIndicatorLights(byte);
    void updateLights(void);
    void setLights(boolean);
    void setLights(boolean,boolean);
    void setLights(boolean,boolean,boolean);
    //static const unsigned char maxLeds;
    static const unsigned char pinMap[MaxLeds];
    static unsigned char ledStates[MaxLeds];
  private:
    unsigned char _curled;
};

#endif // NovaBlinky_h
