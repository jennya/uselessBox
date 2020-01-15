#ifndef SWITCH_H
#define SWITCH_H

#include "Arduino.h"
#include "median.h"

class Switch
{
  public:
    enum State
    {
        Arm = 0,
        Off,
        Light
    };

  public:
    Switch(int pinAssignment, int sampleSize);
    State GetState();
     
  private:
    int m_state;
    int m_pin;
    RunningMedian m_samples;
};

#endif
