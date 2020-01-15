#include "switch.h"

Switch::Switch(int pinAssignment, int sampleSize) : 
      m_state(Off),
      m_pin(pinAssignment),
      m_samples(sampleSize)
{
  // empty
}
    
Switch::State Switch::GetState()
{
    for (int i=0; i<10; ++i)
    {
      m_samples.add(analogRead(m_pin));    
    }
    int switchValue = m_samples.getMedian();
  
    State state;
    if(switchValue > 900)
    { 
      state = Light;
    }
    else if(switchValue > 500) 
    {
      state = Arm;
    }
    else 
    {
      state = Off;
    }

    if (m_state != state) 
    {
      m_state = state;
    }

    return m_state;
}
