#ifndef BOX_H
#define BOX_H

#include "Arduino.h"
#include "dimmer.h"
#include "servo.h"
#include "switch.h"

class Box
{ 
  public:
    Box();
    ~Box();
    
    void Initialize(
      int switchPin,
      int potPin,
      int dimmerPin,
      int servoPin,
      int samplingCount);
      
    void UpdateState();
 
  private:
    void StateTransition(Switch::State state);
    
  private:
    ServoControl *m_pServo;
    Switch *m_pSwitch;
    Dimmer *m_pDimmer;
    
    Switch::State m_prevState;
    unsigned long m_time;
    bool m_sleeping;
};

#endif
