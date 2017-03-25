#ifndef DIGITAL_OUTPUT_H
#define DIGITAL_OUTPUT_H

#include "Arduino.h"
#include "StateMachine.h"

class DigitalOutput : public StateMachine
{
protected:
  DigitalOutput(int pinId);
  ~DigitalOutput() {};

  void SetState(int newState);
  
public:
  virtual void Update(long updateInterval) = 0;
  
  virtual void Reset() = 0;
    
private:
  int m_pinId;
};

#endif
