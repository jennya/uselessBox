
#include "potentiometer.h"

Potentiometer::Potentiometer(int pin, int samplingCount) :
  m_pin(pin),
  m_currentIndex(0),
  m_currentReading(0),
  m_samples(samplingCount)
{
  // empty
}

int Potentiometer::GetValue()
{ 
   for (int i= 0; i < m_samples.getSize(); ++i)
   {
      // get our median value so as to ignore spikes
      m_samples.add(analogRead(m_pin));
   }
  int potReading = m_samples.getMedian();

  // segment the possible values
  // < 50  : Consider this off 
  // < 800 : Utilize majority of pot to control low levels as high level granularity harder to notice
  // >= 800 : Remainder use for higher intensity
  int value;
  if (potReading < 50)
  {
    value = 0;
  }
  else if (potReading < 800)
  {
    value = map(potReading, 50, 800, 50, 100);
  }
  else
  {
    value = map(potReading, 800, 1023, 100, 250);
  }
    
  return value;
}
