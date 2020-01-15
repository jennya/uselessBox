#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#pragma once
#include "Arduino.h"
#include "median.h"

class Potentiometer
{
  public:
    Potentiometer(int pin, int samplingCount);
    
    int GetValue();
    int GetValueDebug();
    
  private:   
    int m_pin;
    int m_currentIndex;
    int m_currentReading;
    RunningMedian m_samples;
};

#endif
