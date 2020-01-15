#include "box.h"

Box::Box() :
  m_pServo(nullptr),
  m_pSwitch(nullptr),  
  m_pDimmer(nullptr),
  m_prevState(Switch::Off),
  m_time(millis()),
  m_sleeping(false)
{
  // empty
}

Box::~Box()
{
  delete m_pDimmer;
  delete m_pSwitch;
  delete m_pServo;
}

void Box::Initialize(
  int switchPin,
  int potPin,
  int dimmerPin,
  int servoPin,
  int samplingCount)
{
  m_pDimmer = new Dimmer(dimmerPin, potPin, samplingCount);
  m_pSwitch = new Switch(switchPin, samplingCount);
  m_pServo = new ServoControl(servoPin);
  m_pServo->Sleep();
}

void Box::UpdateState()
{
  Switch::State switchState = m_pSwitch->GetState();
  StateTransition(switchState);   
}

void Box::StateTransition(Switch::State state)
{    
  bool stateChange = m_prevState != state;

  switch (state)
  {
    case Switch::Off:
    {
      if (stateChange)
      {      
        if (m_prevState == Switch::Arm)
        {
          // just retract the arm, we don't care about play timing here
          m_pServo->Retract();
        }
        else if (m_prevState == Switch::Light)
        {
          // turn off our light as we don't need it
          m_pDimmer->Off();
        }

        // begin timer capture so we can sleep our state(s)
        m_time = millis();
        m_sleeping = false;
      }

      // if we've been idle for more than 10 seconds, turn off the servos
      if (!m_sleeping && 
        millis() - m_time > 10000)
      {
        m_pServo->Sleep();
        m_sleeping = true;
      }
      
      break;
    }

    case Switch::Light:
    {  
      // sleep the servo as we don't need it to respond to shit
      m_pServo->Sleep();
      
      m_pDimmer->On();
                           
      break;
    }

    case Switch::Arm:
    {   
      // turn off the dimmer 
      // TODO - prob unnecessary due to Off state catch
      m_pDimmer->Off();
      
      m_pServo->Extend();
      break;
    }      
  } 
  
  m_prevState = state;
}
