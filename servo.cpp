#include "servo.h"

ServoControl::ServoControl(int pin) :
  m_pin(pin),
  m_currentPosition(Home),
  m_sleeping(false)
{
  m_pPwm = new Adafruit_PWMServoDriver();
  m_pPwm->begin();
  m_pPwm->setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  m_pPwm->setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  // reset to home
  GoToAngle(Home);
}

ServoControl::~ServoControl()
{
  delete m_pPwm;
}

void ServoControl::GoToAngle(int angle)
{
  Wakeup();
  
  if (angle <= Position::Home || angle >= Position::Switch)
  { 
    int pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    m_pPwm->setPWM(m_pin, 0, pulselength);
  }

  delay(100);  // TODO - move to millis timing and remove blocking delays 
}

void ServoControl::Extend()
{
  GoToAngle(Switch);
}
void ServoControl::Retract()
{
  GoToAngle(Home);
}

void ServoControl::Wakeup()
{
  if (m_sleeping)
  {
    m_pPwm->wakeup();
    m_sleeping = false;
  }
}

void ServoControl::Sleep()
{
  if (!m_sleeping)
  {
    m_pPwm->sleep();
    delay(500);   // TODO - move to millis timing and remove blocking delays 
    m_sleeping = true;
  }
}

bool ServoControl::IsSleeping()
{
  return m_sleeping;
}
