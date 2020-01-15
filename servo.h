#ifndef SERVO_H
#define SERVO_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int SERVOMIN = 110;     // This is the 'minimum' pulse length count (out of 4096)
const int SERVOMAX = 480;     // This is the 'maximum' pulse length count (out of 4096)
const int USMIN = 600;        // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
const int USMAX = 2400;       // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
const int SERVO_FREQ = 50 ;   // Analog servos run at ~50 Hz updates

class ServoControl
{
  public:
    enum Position
    {
      Home = 130,
      Switch = 40,
      SwitchAlmost = 80,
      LidPeek = 100,      
    };
    
  public:
    ServoControl(int pin);
    ~ServoControl();
    void Perform(Position endPosition);
    void Perform(Position endPosition, int timeMs);

    void Extend();
    void Retract();
    void Sleep();
    void Wakeup();
    bool IsSleeping();

  private:
    void GoToAngle(int angle);
 
  private:
    Adafruit_PWMServoDriver *m_pPwm;
    int m_pin;
    Position m_currentPosition;
    bool m_sleeping;    
};

#endif
