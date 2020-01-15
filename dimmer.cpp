#include "dimmer.h"

Dimmer::Dimmer(int dimmerPin, int potPin, int samplingCount) :
  m_pin(dimmerPin),
  m_currentValue(0)
{
  m_pot = new Potentiometer(potPin, samplingCount);
  
  pinMode(m_pin, OUTPUT);  
  analogWrite(m_pin, 0);
}

Dimmer::~Dimmer()
{
  delete m_pot;
}

void Dimmer::On()
{
  int value = m_pot->GetValue();

  // pot input should already be smoothed but update PWM signal on values > than
  // threshold to prevent light flickering (TODO - play w/ value?)
  int threshold = abs(m_currentValue - value); 
  if (threshold > 3)
  {  
    m_currentValue = value;
    analogWrite(m_pin, value);
    delay(100);
  }
}

void Dimmer::Off()
{
  if (m_currentValue > 0)
  {
    m_currentValue = 0;
    analogWrite(m_pin, 0);
  }
}
