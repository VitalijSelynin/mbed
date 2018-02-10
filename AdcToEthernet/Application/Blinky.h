///////////////////////////////////////////////////////////
//  Blinky.h
//  Definition of the Template Class Blinky
//  Created on:      10-Feb-2017 23:08:36
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef BLINKY_H
#define BLINKY_H

#include "mbed.h"

template<PinName T>
class Blinky
{
public:
  void Toggle(void)
  {
    led = !led;
  }
  void ToggleWait(void)
  {
    Toggle();
    wait(0.5);
  }
  Blinky()
  :led(T)
  {}

private:
DigitalOut led;
 
};

#endif // BLINKY_H
