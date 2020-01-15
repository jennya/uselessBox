#ifndef DIMMER_H
#define DIMMER_H

#include "Arduino.h"
#include "potentiometer.h"

class Dimmer
{
  public:
    Dimmer(int dimmerPin, int potPin, int samplingCount);
    ~Dimmer();
    void On();
    void Off();
    
  private:
    int m_pin;
    int m_currentValue;
    Potentiometer* m_pot;
};

#endif
