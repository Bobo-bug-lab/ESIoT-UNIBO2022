#ifndef __TEMPSENSORIMPL__
#define __TEMPSENSORIMPL__

#include "TempSensor.h"

class TempSensorImpl: public TempSensor {
 
public: 
  TempSensorImpl(int pin);
  void sync();
  float getTemp();
  float temp; 
  
private:
  int pin;
  bool detected;
};

#endif
