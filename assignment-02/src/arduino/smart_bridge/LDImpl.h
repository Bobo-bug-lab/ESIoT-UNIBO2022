#ifndef __LDIMPL__
#define __LDIMPL__
#define PHOTORES_PIN A0
#define FREQ 5
#define PERIOD 1000/FREQ

#include "LightDetector.h"

class LDImpl: public LightDetector { 
public:
  LDImpl(int pin);
  double light_detect();
  virtual void sync();
  long getLastSyncTime();
private:
  int pin;
  bool detected;  
};

#endif
